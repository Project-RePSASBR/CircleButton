#include <string.h>
#include <stdlib.h>
#include <cell/cell_fs.h>

#include "exports.hpp"

void HexDump(const char *desc, const void *addr, const int len, int per_line)
{
	unsigned int i;
	unsigned int idx;
	unsigned char *buff;
	const unsigned char *pc = (const unsigned char *)addr;
	const unsigned int base = (const unsigned int)addr;

	buff = (unsigned char *)malloc(static_cast<size_t>(per_line));
	if (!buff)
	{
		printf("Hex Dump Error: Unable to allocate memory for buffer.\n");
		return;
	}

	// Silently ignore silly per-line values
	if (per_line < 4 || per_line > 64)
		per_line = 16;

	// Output description if given
	if (desc)
		printf("%s:\n", desc);

	// Length Checks
	if (len == 0)
	{
		printf("Hex Dump Error: Zero Length\n");
		return;
	}

	if (len < 0)
	{
		printf("Hex Dump Error: Negative Length\n");
		return;
	}

	// Process every byte in data
	for (i = 0, idx = 0; i < len; i++)
	{
		if (i == 0)
			printf("  %04x: ", base + i);

		// Multiple of per_line means new or first line (with line offset)
		if (idx == per_line)
		{
			idx = 0;
			if (i != 0)
				printf("  %s\n", buff);

			// Output the offset of current line
			printf("  %04x: ", base + i);
		}

		// Now the hex code for the specific character
		printf(" %02x", pc[i]);

		// And buffer a printable ASCII character for later
		if (pc[i] < 0x20 || pc[i] > 0x7e)
			buff[idx] = '.';
		else
			buff[idx] = pc[i];

		buff[idx + 1] = '\0';
		idx++;
	}

	// Pad out the last line if not exact per_line characters
	while (idx != per_line)
	{
		printf("   ");
		idx++;
	}

	// And print the final ASCII buffer
	printf("  %s\n", buff);

	free(buff);
	buff = nullptr;
}

int CellFsRmRf(const char* path)
{
	int read_e;
	CellFsDirent dir;
	int ret = cellFsOpendir(path, &read_e);
	if (ret != CELL_FS_SUCCEEDED)
		return ret;
	while (true)
	{
		ret = cellFsReaddir(read_e, &dir, nullptr);
		if (ret != CELL_FS_SUCCEEDED || dir.d_namlen == 0)
			break;
		if (strcmp(dir.d_name, ".") == 0 || strcmp(dir.d_name, "..") == 0)
			continue;
		char full_path[1024];
		snprintf(full_path, sizeof(full_path), "%s/%s", path, dir.d_name);
		if (dir.d_type == CELL_FS_TYPE_DIRECTORY)
		{
			ret = CellFsRmRf(full_path);
			if (ret != CELL_FS_SUCCEEDED)
				return ret;
		}
		else
		{
			ret = cellFsUnlink(full_path);
			if (ret != CELL_FS_SUCCEEDED)
				return ret;
		}
	}
	cellFsClosedir(read_e);
	if (ret == 0)
		ret = cellFsRmdir(path);

	return ret;
}

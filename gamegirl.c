#include "includes/gamegirl.h"

int main(int argc, char **argv)
{
	printf("GameGirl - A C-21 Multiplatform Game Boy Emulator\n");

	// Check for commandline arguments
	if (argc < 2)
	{
		printf("Usage: ./gamegirl [progname]\n");
		return EXIT_FAILURE;
	}


	const char *m_filename = argv[1];

	printf("Progname: %s\n", m_filename);

	FILE *m_prg;
	m_prg = fopen(m_filename, "rb");
}
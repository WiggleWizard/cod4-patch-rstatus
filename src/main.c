/* 
 * File:   main.c
 * Author: Terence-Lee "Zinglish" Davis
 * Bug found by Terence-Lee "Zinglish" Davis
 * Patch by Terence-Lee "Zinglish" Davis
 * 
 * Created on 19 February 2014, 15:53
 */

#include <stdio.h>

int main(int argc, char** argv)
{
	/* Ensure we have the filename as the argument */
	if(argc != 2)
	{
		printf("Usage: %s [filename]\n", argv[0]);
		printf("Where [filename] is the CoD4 server ELF\n");
	}
	/* Open the ELF for reading and buffering to patch the short byte */
	else
	{
		FILE* file = fopen(argv[1], "rb+");
		
		if(file == 0)
			printf("Could not open %s for reading/writing\n", argv[1]);
		else
		{
			char byte_check[2];
			char magic_byte[1] = { 0x15 };
			
			fseek(file, 0x001305E2 - 1, SEEK_SET); // Magic number - 1 ;)
			fread(&byte_check, 1, 2, file);
			
			/* Double check the ELF and make sure the byte that needs to be
			   patched is there, then attempt a patch */
			if(byte_check[0] == 0x04 && byte_check[1] == 0x14)
			{
				printf("Patching ELF\n");

				/* Write the byte */
				fseek(file, 0x001305E2, SEEK_SET);
				fwrite(&magic_byte, 1, 1, file);
				
				/* Double check the patch */
				fseek(file, 0x001305E2, SEEK_SET);
				fread(&byte_check, 1, 1, file);
				
				if(byte_check[0] == 0x15)
					printf("Patch successful\n");
				else
					printf("Patch failed\n");
			}
			else if(byte_check[1] == 0x15)
				printf("ELF already patched\n");
			else
				printf("Incorrect CoD4 ELF, not patching\n");
		}
	}
	
	return(1);
}
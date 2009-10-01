This folder contains all the files needed for a project template when building a C project using The CodeSourcery GNU ARM compiler. It is based on the 2008q3 distribution although nothing in here should depend upon the exact version.

the Makefile is in two parts to make it easier to edit only hat part needed by most projects. The Makefile itself simply defines the source files and the target name and then includes makefile.mk for all the actual work.

The project assumes you will be using the ST Peripheral Driver Library V3. The installation location for this library is defined in Makefile.mk

The folder should contain at least the following files:
	main.c
	Makefile
	makefile.mk
	README.TXT
	startup_stm32f10x.c
	stm32f10x.h
	stm32f10x_conf.h
	stm32f10x_flash_md.ld
	stm32f10x_it.c
	stm32f10x_it.h

	
The template is a complete, but completely useless, program in its own right. It will build and produce output files so that you can test your toolchain setup.

To start a specific project, copy all this into a new folder. Change to that folder and run make. If everything is set up correctly, you should get a bunch of object files, a couple of listings and, by default, a .bin file containing the image to be written to the processor. The settings in the linker script and makefile.mk assume the use of the STM32F103RBT6 processor.

Assuming you want to use the Peripheral Driver Library, open stm32f10x_conf.h and uncomment the lines corresponding to the subsystems you wish to use.

The interrupt handlers are defined in the stm32f103x_it.c file. If you have a look in the startup code in startup_stm32f10x.c, you will see that al the interrupt handlers are defined thers with the WEAK attribute and they all point to a default handler that just runs an endless loop. the WEAK atribute means that you are able to define another interrupt handler of the same name in another source file and it will override the one in the startup code. this is how the stm32f103x_it.c file is able to have apparently duplicate interrupt handlers to the startup code. 

If it is more convenient, individual handlers could be placed in their own source files.

Peter Harrison
May 2009
http://www.micromouseonline.com/
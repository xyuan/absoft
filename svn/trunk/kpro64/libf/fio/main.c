void MAIN__(void);

#ifndef __CYGWIN__
int main(int argc, char **argv)
{
	__f90_set_args(argc, argv);

        MAIN__();
        exit(0);
        return (0);
}

#endif


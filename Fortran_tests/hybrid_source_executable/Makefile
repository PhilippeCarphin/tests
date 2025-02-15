
ifeq ($(FC),f77)
	FC = gfortran
endif

ifeq ($(build_dir),)
	$(error "Build dir must be specified", piss )
endif

$(build_dir)/%.o:%.F90
	$(FC) -c -o $@ $<

$(build_dir)/fhybrid: $(build_dir)/main.o $(build_dir)/subroutines.o
	$(FC) -o $@ $^



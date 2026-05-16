SHELL := /bin/bash

LIBFT_DIR := libft

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)
endif

LIB_NAME := libft_malloc_$(HOSTTYPE).so

all:
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean

fclean:
	$(MAKE) -C $(LIBFT_DIR) fclean

re:
	$(MAKE) -C $(LIBFT_DIR) re

test:
	@echo $(HOSTTYPE)
	@echo $(LIB_NAME)
	@echo "Not Implemented Yet"

# use this function to create a symbolic link to the libft_malloc_$(HOSTTYPE).so to
# libft_malloc.so due project requirements.
define create_sin_link
	@ln -sf $(LIB_NAME) libft_malloc.so
endef
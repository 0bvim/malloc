SHELL := /bin/bash

LIBFT_DIR := libft

all:
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean

fclean:
	$(MAKE) -C $(LIBFT_DIR) fclean

re:
	$(MAKE) -C $(LIBFT_DIR) re

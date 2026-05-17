/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 22:55:26 by vde-frei          #+#    #+#             */
/*   Updated: 2026/05/16 21:33:45 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_MALLOC_H
#define MALLOC_MALLOC_H

# include <sys/mman.h>
# include <stdbool.h>

#if defined(__APPLE__) && defined(__MACH__)
#define GET_DEFAULT_PAGE_SIZE() getpagesize()

#elif defined(__linux__)
#define GET_DEFAULT_PAGE_SIZE() sysconf(_SC_PAGESIZE)

#else
/* fallback */
#define GET_DEFAULT_PAGE_SIZE() 4096
#endif

enum
{
    OFFSET_IGN = 0, // In macOS, it must be zero when use MAP_ANON flag.
    FD_IGN = -1, // In macOS, it must be '-1' when use MAP_ANON flag.
    DEFAULT_PROT = PROT_READ | PROT_WRITE,
    DEFAULT_FLAGS = MAP_ANON | MAP_PRIVATE,
    TINY = 256,
    SMALL = 14336
};

typedef struct s_alloc t_alloc;

struct s_alloc
{
    size_t requested_size;
    bool allocated;
    t_alloc* next;
    t_alloc* prev;
};

// libft includes
# include "../../libft/includes/bool.h"
# include "../../libft/includes/ft_memory.h"
# include "../../libft/includes/ft_put.h"
# include "../../libft/includes/ft_string.h"
# include "../../libft/includes/libft.h"
# include "../../libft/includes/list.h"

// functions prototype
void* malloc(size_t size);

#endif //MALLOC_MALLOC_H

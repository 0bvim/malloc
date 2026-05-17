/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 12:18:07 by vde-frei          #+#    #+#             */
/*   Updated: 2026/05/16 21:26:26 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include "../malloc/src/malloc/malloc.h"

int main()
{
    char* ptr;
    //ptr = mmap(NULL, GET_DEFAULT_PAGE_SIZE(), DEFAULT_PROT, DEFAULT_FLAGS, FD_IGN, OFFSET_IGN);
    char* ptr2 = malloc(0);
    printf("Address: %p\nSize: %lu\nPage Size: %d\n", ptr, sizeof(ptr), getpagesize());

    if (ptr == MAP_FAILED)
        return perror("Fail to map block of memory"), 0;

    ptr[0] = 'a';
    ptr2[0] = 'a';
    puts("-----------------------------------------------------");
    printf("Value: %s\nPage Size: %d\n", ptr, getpagesize());
    puts("-----------------------------------------------------");
    printf("Address A %p\nAddress B %p\n", &ptr[0], &ptr2[0]);

    //munmap(ptr, GET_DEFAULT_PAGE_SIZE());
    free(ptr);
    free(ptr2);
    return 0;
}

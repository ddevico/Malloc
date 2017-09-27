/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 15:15:20 by ddevico           #+#    #+#             */
/*   Updated: 2017/09/27 11:31:28 by ddevico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int					main(void)
{
	int				i;
	char			*s1, *s2, *s3, *s4, *s5, *s6, *s7, *s8, *s9, *s10, *s11,
					*s12, *s13, *s14, *s20;

	i = -1;
	s1 = (char *)malloc(sizeof(char) * 21);
	if (s1)
	{
		while (++i < 10)
			s1[i] = 'a';
		s1[i] = '\0';
		i = -1;
	}
	s2 = (char *)malloc(sizeof(char) * 500);
	if (s2)
	{
		while (++i < 10)
			s2[i] = 'b';
		s2[i] = '\0';
		i = -1;
	}
	s3 = (char *)malloc(sizeof(char) * 200);
	if (s3)
	{
		while (++i < 10)
			s3[i] = 'c';
		s3[i] = '\0';
		i = -1;
	}
	s4 = (char *)malloc(sizeof(char) * 10);
	if (s4)
	{
		while (++i < 10)
			s4[i] = 'd';
		s4[i] = '\0';
		i = -1;
	}
	s5 = (char *)malloc(sizeof(char) * 11);
	if (s5)
	{
		while (++i < 10)
			s5[i] = 'e';
		s5[i] = '\0';
		i = -1;
	}
	s6 = (char *)malloc(sizeof(char) * 400);
	if (s6)
	{
		while (++i < 10)
			s6[i] = 'f';
		s6[i] = '\0';
		i = -1;
	}
	s7 = (char *)malloc(sizeof(char) * 400);
	if (s7)
	{
		while (++i < 10)
			s7[i] = 'g';
		s7[i] = '\0';
		i = -1;
	}
	s8 = (char *)malloc(sizeof(char) * 1000);
	if (s8)
	{
		while (++i < 10)
			s8[i] = 'h';
		s8[i] = '\0';
		i = -1;
	}
	s9 = (char *)malloc(sizeof(char) * 300);
	if (s9)
	{
		while (++i < 10)
			s9[i] = 'i';
		s9[i] = '\0';
		i = -1;
	}
	s10 = (char *)malloc(sizeof(char) * 9000);
	if (s10)
	{
		while (++i < 10)
			s10[i] = 'j';
		s10[i] = '\0';
		i = -1;
	}
	show_alloc_mem();
	/*ft_printf("\n\n\n\n\n\n\n");
	  free(s4);
	  free(s3);
	  show_alloc_mem();
	  s11 = (char *)malloc(sizeof(char) * 205);
	  if (s11)
	  {
	  while (++i < 100)
	  s11[i] = '1';
	  s11[i] = '\0';
	  i = -1;
	  }
	  ft_printf("\n\n\nnew\n\n\n");
	  show_alloc_mem();
	  free(s1);
	  show_alloc_mem();
	  free(s2);
	  show_alloc_mem();
	  free(s3);
	  show_alloc_mem();
	  free(s4);
	  show_alloc_mem();
	  free(s5);
	  show_alloc_mem();
	  free(s6);
	  show_alloc_mem();
	  free(s7);
	  show_alloc_mem();
	  free(s8);
	  show_alloc_mem();
	  free(s9);
	  show_alloc_mem();
	  free(s10);
	  show_alloc_mem();
	  free(s11);
	  show_alloc_mem();
	  free(s20);
	  show_alloc_mem();
	  i = -1;
	  s1 = (char *)malloc(sizeof(char) * 21);
	  if (s1)
	  {
	  while (++i < 10)
	  s1[i] = 'a';
	  s1[i] = '\0';
	  i = -1;
	  }
	  s2 = (char *)malloc(sizeof(char) * 500);
	  if (s2)
	  {
	  while (++i < 10)
	  s2[i] = 'b';
	  s2[i] = '\0';
	  i = -1;
	  }
	  s3 = (char *)malloc(sizeof(char) * 200);
	  if (s3)
	  {
	  while (++i < 10)
	  s3[i] = 'c';
	  s3[i] = '\0';
	  i = -1;
	  }
	  s4 = (char *)malloc(sizeof(char) * 10);
	  if (s4)
	  {
	  while (++i < 10)
	  s4[i] = 'd';
	  s4[i] = '\0';
	  i = -1;
	  }
	s5 = (char *)malloc(sizeof(char) * 11);
	if (s5)
	{
		while (++i < 10)
			s5[i] = 'e';
		s5[i] = '\0';
		i = -1;
	}
	s6 = (char *)malloc(sizeof(char) * 400);
	if (s6)
	{
		while (++i < 10)
			s6[i] = 'f';
		s6[i] = '\0';
		i = -1;
	}
	s7 = (char *)malloc(sizeof(char) * 400);
	if (s7)
	{
		while (++i < 10)
			s7[i] = 'g';
		s7[i] = '\0';
		i = -1;
	}
	s8 = (char *)malloc(sizeof(char) * 1000);
	if (s8)
	{
		while (++i < 10)
			s8[i] = 'h';
		s8[i] = '\0';
		i = -1;
	}
	s9 = (char *)malloc(sizeof(char) * 300);
	if (s9)
	{
		while (++i < 10)
			s9[i] = 'i';
		s9[i] = '\0';
		i = -1;
	}
	s10 = (char *)malloc(sizeof(char) * 9000);
	if (s10)
	{
		while (++i < 10)
			s10[i] = 'j';
		s10[i] = '\0';
		i = -1;
	}
	show_alloc_mem();
	free(s4);
	free(s3);
	show_alloc_mem();
	ft_printf("\n\n\nnew\n\n\n");
	s12 = (char *)calloc(sizeof(char), 10);
	if (s12)
	{
		while (++i < 9)
			s12[i] = '2';
		s12[i] = '\0';
		i = -1;
	}
	show_alloc_mem();*/
	return (0);
}

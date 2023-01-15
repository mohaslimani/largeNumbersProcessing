/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoulaim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 20:24:11 by msoulaim          #+#    #+#             */
/*   Updated: 2020/01/11 08:38:08 by msoulaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef	struct	s_list
{
	int c;
	struct s_list *next;
}				t_list;

/*typedef	struct s_two
{
	t_list *quot;
	t_list *div;
};*/

t_list*	new_node(int i)
{
	t_list *new = (t_list *)malloc(sizeof(t_list));
	new->c = i;
	new->next = NULL;
	return (new);
}

int		ctoi(char c)
{
	if (c > '9' || c < '0')
	{
		puts("are u fucking with me you little shit !");
		exit(1);
	}
	c = c - '0';
	return(c);
}

void	add_end(t_list **head, t_list *new)
{
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	t_list *temp = *head;
	while (temp->next)
	{
		temp = (temp)->next;
	}
	temp->next = new;
}

void	delete_zero(t_list **head)
{
	while (*head && (*head)->c == 0)
		*head = (*head)->next;
	if (*head == NULL)
		*head = new_node(0);
}

t_list*	new_list()
{
	t_list *first = NULL;
	t_list *temp;
	char	c = 0;
	puts("give me numbers :");
	int i = 0;
	while (read(0, &c, 1) > 0 && c != '\n')
	{
		temp = new_node(ctoi(c));
		add_end(&first, temp);
	}
	delete_zero(&first);
	return (first);
}

void	add_front(t_list **head, t_list *new)
{
	new->next = *head;
	*head = new;
}

void	reverse(t_list** head_ref)
{
	t_list* prev = NULL;
	t_list* current = *head_ref;
	t_list* next = NULL;
	while (current != NULL)
	{
		next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head_ref = prev; 
} 
  

t_list*	addition(t_list *first, t_list *second)
{
	t_list *result = NULL;
	t_list *tmp;
	int resu = 0;
	int rest = 0;
	while (first != NULL && second != NULL)
	{
		resu = first->c + second->c + rest;
		rest = resu / 10;
		if (resu >= 10)
		{
			resu = resu % 10;
		}
		add_front(&result, new_node(resu));
		first = first->next;
		second = second->next;
	}
	while (first)
	{
		resu = rest + first->c;
		rest = resu / 10;
		if (resu >= 10)
		{
			resu = resu % 10;
		}
		add_front(&result, new_node(resu));
		first = first->next;
	}
	while (second)
	{
		resu = rest + second->c;
		rest = resu / 10;
		if (resu >= 10)
		{
			resu = resu % 10;
		}
		add_front(&result, new_node(resu));
		second = second->next;
	}
	if (rest != 0 && result != NULL)
	{
		add_front(&result, new_node(rest));
	}
	return (result);
}

void	print_list(t_list *list)
{
	while (list)
	{
		printf("%d", list->c);
		list = list->next;
	}
	puts("");
}

int		list_lengh(t_list *list)
{
	if (list == NULL)
		return (0);
	return (1 + list_lengh(list->next)); 	
}

int		ret_lekbir(t_list *first, t_list *second)
{
	if (list_lengh(first) > list_lengh(second))
		return(1);
	if (list_lengh(first) < list_lengh(second))
		return(2);
	while (first && second)
	{
		if (first->c > second->c)
			return (1);
		if (first->c < second->c)
			return (2);
		first = first->next;
		second = second->next;
	}
	return (0);
}

t_list*		subs_list(t_list *first, t_list *second)
{
	t_list *result = NULL;
	int resu = 0;
	int rest = 0;
	while (second)
	{
		resu = first->c - second->c - rest;
		if (resu < 0)
		{
			resu = resu + 10;
			rest = 1;
		}
		else
		{
			rest = 0;
		}
		add_front(&result, new_node(resu));
		second = second->next;
		first = first->next;
	}
	while (first)
	{
		resu = first->c - rest;
		if (resu < 0)
		{
			resu = resu + 10;
			rest = 1;
		}
		else
		{
			rest = 0;
		}
		add_front(&result, new_node(resu));
		first = first->next;
	}
	delete_zero(&result);
	return (result);
}

//memory leak bzzzzzzzzf

t_list*	multiply_list(t_list *first, t_list *second)
{
	t_list *tmp;
	t_list *result = new_node(0);

	tmp = new_node(1);
	int i = 0;
	while (!(list_lengh(second) == 1 && second->c == 0))
	{
		result = addition(result, first);
		reverse(&result);
		second = subs_list(second, tmp);
		reverse(&second);
		i++;
	}
	reverse(&result);
	return (result);
}

t_list*	quot_rst(t_list *first, t_list *second, t_list **rest)
{
	t_list *quot = new_node(0);
	t_list *one = new_node(1);
	if (list_lengh(second) == 1 && second->c == 1)
	{
		*rest = new_node(0);
		reverse(&first);
		return (first);
	}
	if (list_lengh(second) == 1 && second->c == 0)
	{
		printf("en peut pas diviser par zero ?");
		exit(1);
	}
	if (ret_lekbir(first, second) == 2)
	{
		*rest = first;
		return (quot);
	}
	while (ret_lekbir(first, second) == 1 || ret_lekbir(first, second) == 0)
	{
		first = subs_list(first, second);
		reverse(&first);
		quot = addition(quot, one);
		reverse(&quot);
	}
	reverse(&first);
	reverse(&quot);
	*rest = first;
	return (quot);
}

void	is_prime(t_list *first)
{
	t_list *div = new_node(2);
	t_list *rest = NULL;
	t_list *limit = quot_rst(first, div, &rest);
	reverse(&limit);
	//puts("limits/2 == ");
	//print_list(limit);
	//print_list(first);
	if (ret_lekbir(first, new_node(2)) == 0)
	{
		puts("nice try he is 2 so he is prime");
		return ;
	}
	if (ret_lekbir(rest, new_node(0)) == 0)
	{
		puts("this number is divisibl on two");
		return ;
	}
	//puts("done");
	t_list *one = new_node(1);
	t_list *two = new_node(2);
	t_list *three = new_node(3);
	//t_list *limit = quot_rst(first, two, &rest);
	//quot_rst(first, three, &rest);
	while(ret_lekbir(three, limit) != 1)
	{
		quot_rst(first, three, &rest);
		if (rest->c == 0 && list_lengh(rest) == 1)
		{
			puts("that num is not prime he is devisible by");
			print_list(three);
			return ;
		}
		three = addition(three, two);
		printf("three == ");
		print_list(three);
		puts("");
		reverse(&three);
	}
	puts("priiiiime");
}

void	add_zeros(t_list *first, int i)
{
	if (first == NULL)
		return ;
	while(first->next)
		first = first->next;
	while (i--)
	{
		first->next = (t_list *)malloc(sizeof(t_list));
		first->next->c = 0;
		first = first->next;
	}
	first->next = NULL;
}

t_list*	new_multip(t_list *first, t_list *second)
{
	t_list *tmp2 = NULL;
	t_list *tmp = NULL;
	t_list *tmp3 = new_node(0);
	int i = 0;
	while (first)
	{
		tmp = new_node(first->c);
		tmp2 = multiply_list(tmp, second);
		add_zeros(tmp2, i);
		reverse(&tmp2);
		tmp3 = addition(tmp3, tmp2);
		reverse(&tmp3);
		first = first->next;
		i++;
	}
	reverse(&tmp3);
	return tmp3;
}

t_list* puissance(t_list* first, t_list *second)
{
	t_list *zero = new_node(0);
	t_list *result = new_node(1);
	t_list *one = new_node(1);
	while (ret_lekbir(second, zero) != 0)
	{
		result = new_multip(result, first);
		reverse(&result);
		second = subs_list(second, one);
		reverse(&second);
	}
	reverse(&result);
	return(result);
}

int		main()
{
	t_list *first = NULL;
	t_list *second = NULL;
	t_list *result = NULL;
	//t_list *rest = NULL;
	/*t_list *temp;
	char	c = 0;
	puts("hellloo madafaka give me numbers or get a life");
	int i = 0;
	while (read(0, &c, 1) > 0 && c != '\n')
	{
		temp = new_node(ctoi(c));
		//puts("OwO");
		//if (i++ == 0)
		//	first = temp;
		add_end(&first, temp);
		//puts("oo");
	}*/
	first = new_list();
	//printf("f = %d", list_lengh(first));
	//first = new_list();
	puts("give me another one i am hungry");
	second = new_list();
	//printf("s = %d", list_lengh(second));
	/*while (first)
	{
		printf("%d", first->c);
		first = first->next;
	}
	puts("");
	while (second)
	{
		printf("%d", second->c);
		second = second->next;
	}*/
	//reverse(&first);
	//reverse(&second);
	//result = addition(first, second);
	//print_list(result);

	//reverse(&first);
	//reverse(&second);
	/*if (ret_lekbir(first, second) == 2)
	{
		printf("-");
		print_list(subs_list(second, first));
	}
	else
		print_list(subs_list(first, second));*/

	//printf("lekbir == %d", ret_lekbir(first, second));
	//print_list(first);
	//print_list(second);
	//result = addition(first, second);
	//print_list(result);
	//result = addition(first, result);
	//result = subs_list(first, second);
	//print_list(first);
	/*
	reverse(&first);
	reverse(&second);
	if (ret_lekbir(first, second) == 2)
		result = new_multip(first, second);
	else
	{
		result = new_multip(second, first);
	}
	print_list(result);
*/
		
	//is_prime(first);
/*	
	t_list *rest = NULL;
	reverse(&first);
	reverse(&second);
	result = quot_rst(first, second, &rest);
	print_list(rest);
	print_list(result);
*/

	is_prime(first);
	//puts("\nrest");
	//add_zeros(first, 1);
	//print_list(first);
	//new_multip(first, second);
	//puts("\ntdt");
	//print_list(multiply_list(first, second));
	return (0);
}

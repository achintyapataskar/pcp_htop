#include "process.h"
#include "display.h"
/*!
 * my own function to copy strings of known length.
 */
void mystrcpy(char *to, char *from) {
	for(int i = 0; i < STRING_SIZE; i++)
		to[i] = from[i];
	return;
}
void init_linklist(linklist *l) {
	l->head = NULL;
	return;
}
void create_process(process *p, int pid, float mem, float cpu, char *user_name, char *command) {
	p->pid = pid;
	p->mem = mem;
	p->cpu = cpu;
	p->user_name = (char *)malloc(sizeof(char) * STRING_SIZE);
	p->command = (char *)malloc(sizeof(char) * STRING_SIZE);
	strcpy(p->user_name, user_name);
	strcpy(p->command, command);
	return;
}
void copy_process(process *to, process *from) {
	to->pid = from->pid;
	to->mem = from->mem;
	to->cpu = from->cpu;
	mystrcpy(to->user_name, from->user_name);
	mystrcpy(to->command, from->command);
	return;
}
int compare_process(process *p1, process *p2) {
	if((p1->pid != p2->pid) || (p1->mem != p2->mem) || (p1->cpu != p2->cpu) || (strcmp(p1->user_name, p2->user_name) != 0) || (strcmp(p1->command, p2->command) != 0))
		return 1;
	return 0;
}
void print_process(process *p) {
	printf("%d\t%s\t%s\t%.2f\t%.2f", p->pid, p->user_name, p->command, p->cpu, p->mem);
	return;
}
void w_print_process(process *p) {
	int row, col;
	printw("%d", p->pid);
	getyx(stdscr,row, col);
	move(row, 5);
	printw("%5s", p->user_name);
	move(row, 14);
	printw("%5s", p->command);
	move(row, 25);
	printw("%.2f", p->mem);
	move(row, 31);
	printw("%.2f", p->cpu);
	
//	printw("%d\t%s\t%s\t\t%.2f\t\t%.2f", p->pid, p->user_name, p->command, p->mem, p->cpu);
	return;
}
int add_node_to_linklist(linklist *l, process *p) {
	if(l->head == NULL) {
		l->head = (node *)malloc(sizeof(node));
		create_process(&(l->head->p), 0, 0, 0, "temp", "temp");
		copy_process(&(l->head->p), p);
		l->head->next = NULL;
		return 1;
	}
	node *it = l->head;
	while(it) {
		if(it->p.pid == p->pid) {
			copy_process(&(it->p), p);
			return 2;
		}
		it = it->next;
	}
	it = l->head;
	while(it->next)
		it = it->next;
	it->next = (node *)malloc(sizeof(node));
	create_process(&(it->next->p), 0, 0, 0, "temp", "temp");
	copy_process(&(it->next->p), p);
	it->next->next = NULL;
	return 0;
}
node *find_node(linklist *l, process *p) {
	node *it = l->head;
	while(it) {
		if(compare_process(&(it->p), p) == 0)
			return it;
		it = it->next;
	}
	return it;
}
void insert_node (linklist *l, node *after, node *input) {
	if(after == NULL) {
		node *t = (node *)malloc(sizeof(node));
		t->next = l->head;
		create_process(&(t->p), 0, 0, 0, "temp", "temp");
		copy_process(&(t->p), &(input->p));
		l->head = t;
		return;
	}
	node *it = l->head, *copy;
	while(it && it != after)
		it = it->next;
	if(it == NULL)
		return;
	copy = it->next;
	it->next = (node *)malloc(sizeof(node));
	create_process(&(it->next->p), 0, 0, 0, "temp", "temp");
	copy_process(&(it->next->p), &(input->p));
	it->next->next = copy;
	return;
}
int insert_process(linklist *l, process *after_p, process *input) {
	node *after = find_node(l, after_p);
	node *copy = after->next;
	after->next = (node *)malloc(sizeof(node));
	create_process(&(after->next->p), 0, 0, 0, "temp", "temp");
	copy_process(&(after->next->p), input);
	after->next->next = copy;
	return 0;
}
void delete_node(linklist *l, node *to_delete) {
	if(l->head == NULL)
		return;
	if(to_delete == l->head) {
		l->head = l->head->next;
		free(l->head);
		return;
	}
	node *i, *j;
	i = l->head;
	while(i) {
		if(i == to_delete)
			break;
		j = i;
		i = i->next;
	}
	if(i == NULL)
		return;
	j->next = i->next;
	free(i);
}
void linklist_no_sort() {
	return;
}
void linklist_sort_process(linklist *l) {
	node *p, *q, *max;
	process temp;
	create_process(&temp, 0, 0, 0, "temp", "temp");
	for(p = l->head; p != NULL; p = p->next) {
		max = p;
		for(q = p->next; q != NULL; q = q->next) {
			if(q->p.pid > max->p.pid)
				max = q;
		}
		copy_process(&temp, &(max->p));
		copy_process(&(max->p), &(p->p));
		copy_process(&(p->p), &temp);
	}
}
void linklist_sort_cpu(linklist *l) {
	node *p, *q, *max;
	process temp;
	create_process(&temp, 0, 0, 0, "temp", "temp");
	for(p = l->head; p != NULL; p = p->next) {
		max = p;
		for(q = p->next; q != NULL; q = q->next) {
			if(q->p.cpu > max->p.cpu)
				max = q;
		}
		copy_process(&temp, &(max->p));
		copy_process(&(max->p), &(p->p));
		copy_process(&(p->p), &temp);
	}
}
void linklist_sort_mem(linklist *l) {
	node *p, *q, *max;
	process temp;
	create_process(&temp, 0, 0, 0, "temp", "temp");
	for(p = l->head; p != NULL; p = p->next) {
		max = p;
		for(q = p->next; q != NULL; q = q->next) {
			if(q->p.mem > max->p.mem)
				max = q;
		}
		copy_process(&temp, &(max->p));
		copy_process(&(max->p), &(p->p));
		copy_process(&(p->p), &temp);
	}
}
int print_linklist(linklist *l) {
	int no_of_printed_nodes = 0;
	node *it = l->head;
	while(it) {
		w_print_process(&(it->p));
		printf("\n");
		it = it->next;
		no_of_printed_nodes++;
	}
	return no_of_printed_nodes;
}
int print_top_n_linklist(linklist *l, int n) {
	int no_of_printed_nodes = 0;
	node *it = l->head;
	int i = 0;
	while(it && i < n) {
		w_print_process(&(it->p));
		printw("\n");
		it = it->next;
		i++;
		no_of_printed_nodes++;
	}	
	return no_of_printed_nodes;
}

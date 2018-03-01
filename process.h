#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*!
 * STRING_SIZE sets the length of username and command in the process data structure.
 */
#define STRING_SIZE 128
/*!
 * The process data structure includes the following:
 * 1. Process ID: pid
 * 2. Memory Consumption Percentage: mem
 * 3. CPU Consumption Percentage: cpu
 * 4. User Name: user_name
 * 5. Command: cmd
 */
typedef struct process {
	int pid;
	float mem, cpu;
	char *user_name, *command;
}process;
/*!
 * The node in the linklist being used for capturing process data.
 * Contains a process and a pointer to the next node in the list.
 * The next node points to NULL if it is the last node in the list.
 */
typedef struct node {
	process p;
	struct node *next;
}node;
/*!
 * The list of processes is stored in memory using a singly linked list.
 * linklist data structure basically holds a pointer to the first node in any list.
 * linklist allows for dynamic allocation of new processes and other required funcitons such as sorting, displaying etc.
 */
typedef struct linklist {
	node *head;
}linklist;
/*!
 * This is the globally available data structure that holds all information of all processes in memory.
 */
linklist process_list;
/*!
 * Add a new information to a new process.
 * User must declare a process variable first and then use it's address to fill it in.
 */
void create_process(process *p, int pid, float mem, float cpu, char *user_name, char *command);
/*!
 * Copies contents of process pointed to by *from to the process pointed to by *to.
 * User must have declare both processes first, and then use their addresses in the function parameters.
 */
void copy_process(process *to, process *from);
/*!
 * This function returns 0 in case contents of both processes are same. Otherwise it returns a non - zero value.
 */
int compare_process(process *p1, process *p2);
/*!
 * This function prints the information of a process in the order:
 * PID, User Name, Command, Memory, CPU
 * to the terminal.
 * Mostly used for testing the contents of a process.
 */
void print_process(process *p);
/*!
 * This function is similar to print_process, but instead of printing process information to terminal it prints process information to the window currently created by ncurses.
 */
void w_print_process(process *p);
/*!
 * Initialises head pointer of linklist to NULL.
 * This indicates that the linklist currently holds no contents.
 */
void init_linklist(linklist *l);
/*!
 * Add a new process or update information of an already existing process in the process_list.
 */
int add_node_to_linklist(linklist *l, process *p);
/*!
 * Returns a pointer to the node in which process information is matched to process information in p.
 */
node *find_node(linklist *l, process *p);
/*!
 * This function is used to insert a node in the linklist after the node containing process pointed to by after. A new node is added and it contains the information of the process pointed to by input. Function returns non - zero value if no node matching after was found. Funtion returns zero if node was successfully inserted. If user wishes to add node before head in the linklist, set after = NULL.
 */
int insert_process(linklist *l, process *after, process *input);
/*!
 * This function is used to insert a node in the linklist after the node containing process pointed to by after. A new node is added and it contains the information of the process pointed to by input. Function returns non - zero value if no node matching after was found. Funtion returns zero if node was successfully inserted. If user wishes to add node before head in the linklist, set after = NULL.
 */
void insert_node(linklist *l, node *after, node *input);
/*!
 * Delete a node which is pointed to by to_delete
 */
void delete_node(linklist *l, node *to_delete);
/*!
 * Sort the linklist based on process IDs
 */
void linklist_sort_process(linklist *l);
/*!
 * Sort the linklist based on CPU consumption
 */
void linklist_sort_cpu(linklist *l);
/*!
 * Sort the linklist based on Memory consumption
 */
void linklist_sort_mem(linklist *l);
/*!
 * Do not modify list after insertion of new processes.
 */
void linklist_no_sort();
/*!
 * Print the entire link list to the terminal.
 */
int print_linklist(linklist *l);
/*!
 * Print the first n nodes of the linklist to window defined by ncurses
 */
int print_top_n_linklist(linklist *l, int n);

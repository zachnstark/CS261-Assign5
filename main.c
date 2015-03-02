#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "toDoList.h"


int main (int argc, const char * argv[])
{
  char *filename;
  char *description;
  int priority;
  char cmd = ' ';
  DynArr* mainList = createDynArr(10);

  printf("\n\n** TO-DO LIST APPLICATION **\n\n");

  do
    {
      printf("Press:\n"
             "'l' to load to-do list from a file\n"
             "'s' to save to-do list to a file\n"
             "'a' to add a new task\n"
             "'g' to get the first task\n"
             "'r' to remove the first task\n"
             "'p' to print the list\n"
             "'e' to exit the program\n"
             );
      /* get input command (from the keyboard) */
      cmd = getchar();
      /* clear the trailing newline character */
      while (getchar() != '\n');

      switch (cmd)
      {
	 case 'l':
	    scanf("Please enter the filename: %s \n", filename);
	    FILE *reader = fopen(filename, "r");
	    loadList(mainList, reader);
	 case 's':
	    scanf("Please enter the filename: %s \n", filename);
	    FILE *writer = fopen(filename, "w+");
	    saveList(mainList, writer);
	 case 'a':
	    scanf("Please enter the task description: %s \n", description);
	    scanf("Please enter the task priority (0-999): %d \n", priority);
	    TaskP dummy = createTask(priority, description);
	    addHeap(mainList, dummy, compare);
	    printf("The task '%s' has been added to the to-do list.\n", description);
	 case 'g':
	    if (!isEmptyDynArr(mainList))
	       printf("The first task is %s \n", ((struct Task *)getMinHeap(mainList))->description);
	    else
	       printf("Your to-do list is empty!\n");
	 case 'r':
	    description = ((struct Task *)getMinHeap(mainList))->description;
	    removeMinHeap(mainList, compare);
	    printf("Your first task '%s' has been removed from the list.\n");
	 case 'p':
	    printList(mainList);
	 case 'e':
	    printf("Bye!");
      }

      /* Note: We have provided functions called printList(), saveList() and loadList() for you
         to use.  They can be found in toDoList.c */
    }
  while(cmd != 'e');
  /* delete the list */
  deleteDynArr(mainList);

  return 0;
}

/* Program to assist in the challenge of solving sudoku puzzles.

   Skeleton program written by Alistair Moffat, ammoffat@unimelb.edu.au,
   August 2021, with the intention that it be modified by students
   to add functionality, as required by the assignment specification.

   Student Authorship Declaration:

   (1) I certify that except for the code provided in the initial skeleton
   file, the  program contained in this submission is completely my own
   individual work, except where explicitly noted by further comments that
   provide details otherwise.  I understand that work that has been developed
   by another student, or by me in collaboration with other students, or by
   non-students as a result of request, solicitation, or payment, may not be
   submitted for assessment in this subject.  I understand that submitting for
   assessment work developed by or in collaboration with other students or
   non-students constitutes Academic Misconduct, and may be penalized by mark
   deductions, or by other penalties determined via the University of
   Melbourne Academic Honesty Policy, as described at
   https://academicintegrity.unimelb.edu.au.

   (2) I also certify that I have not provided a copy of this work in either
   softcopy or hardcopy or any other form to any other student, and nor will I
   do so until after the marks are released. I understand that providing my
   work to other students, regardless of my intention or any undertakings made
   to me by that other student, is also Academic Misconduct.

   (3) I further understand that providing a copy of the assignment
   specification to any form of code authoring or assignment tutoring service,
   or drawing the attention of others to such services and code that may have
   been made available via such a service, may be regarded as Student General
   Misconduct (interfering with the teaching activities of the University
   and/or inciting others to commit Academic Misconduct).  I understand that
   an allegation of Student General Misconduct may arise regardless of whether
   or not I personally make use of such solutions or sought benefit from such
   actions.

   Signed by: [Tony Yong He, 1269440]
   Dated:     [01/09/2021]

*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* these #defines provided as part of the initial skeleton */

#define NDIM 3		/* sudoku dimension, size of each inner square */
#define NDIG (NDIM*NDIM)
			/* total number of values in each row */
#define NGRP 3		/* number of sets each cell is a member of */
#define NSET (NGRP*NDIG)
			/* total number of sets in the sudoku */
#define NCLL (NDIG*NDIG)
			/* total number of cells in the sudoku */

#define ERROR	(-1)	/* error return value from some functions */

/* these global constant arrays provided as part of the initial skeleton,
   you may use them in your code but must not alter them in any way,
   regard them as being completely fixed. They describe the relationships
   between the cells in the sudoku and provide a basis for all of the
   sudoku processing loops */

/* there are 27 different different sets of elements that need to be
   checked against each other, this array converts set numbers to cells,
   that's why its called s2c */
int s2c[NSET][NDIM*NDIM] = {
	/* the first group of nine sets describe the sudoku's rows */
	{  0,  1,  2,  3,  4,  5,  6,  7,  8 },
	{  9, 10, 11, 12, 13, 14, 15, 16, 17 },
	{ 18, 19, 20, 21, 22, 23, 24, 25, 26 },
	{ 27, 28, 29, 30, 31, 32, 33, 34, 35 },
	{ 36, 37, 38, 39, 40, 41, 42, 43, 44 },
	{ 45, 46, 47, 48, 49, 50, 51, 52, 53 },
	{ 54, 55, 56, 57, 58, 59, 60, 61, 62 },
	{ 63, 64, 65, 66, 67, 68, 69, 70, 71 },
	{ 72, 73, 74, 75, 76, 77, 78, 79, 80 },
	/* the second group of nine sets describes the sudoku's columns */
	{  0,  9, 18, 27, 36, 45, 54, 63, 72 },
	{  1, 10, 19, 28, 37, 46, 55, 64, 73 },
	{  2, 11, 20, 29, 38, 47, 56, 65, 74 },
	{  3, 12, 21, 30, 39, 48, 57, 66, 75 },
	{  4, 13, 22, 31, 40, 49, 58, 67, 76 },
	{  5, 14, 23, 32, 41, 50, 59, 68, 77 },
	{  6, 15, 24, 33, 42, 51, 60, 69, 78 },
	{  7, 16, 25, 34, 43, 52, 61, 70, 79 },
	{  8, 17, 26, 35, 44, 53, 62, 71, 80 },
	/* the last group of nine sets describes the inner squares */
	{  0,  1,  2,  9, 10, 11, 18, 19, 20 },
	{  3,  4,  5, 12, 13, 14, 21, 22, 23 },
	{  6,  7,  8, 15, 16, 17, 24, 25, 26 },
	{ 27, 28, 29, 36, 37, 38, 45, 46, 47 },
	{ 30, 31, 32, 39, 40, 41, 48, 49, 50 },
	{ 33, 34, 35, 42, 43, 44, 51, 52, 53 },
	{ 54, 55, 56, 63, 64, 65, 72, 73, 74 },
	{ 57, 58, 59, 66, 67, 68, 75, 76, 77 },
	{ 60, 61, 62, 69, 70, 71, 78, 79, 80 },
};


/* there are 81 cells in a dimension-3 sudoku, and each cell is a
   member of three sets, this array gets filled by the function 
   fill_c2s(), based on the defined contents of the array s2c[][] */
int c2s[NCLL][NGRP];

void
fill_c2s() {
	int s=0, d=0, c;
	for ( ; s<NSET; s++) {
		/* record the first set number each cell is part of */
		for (c=0; c<NDIM*NDIM; c++) {
			c2s[s2c[s][c]][d] = s;
		}
		if ((s+1)%(NGRP*NDIM) == 0) {
			d++;
		}
	}
#if 0
	/* this code available here if you want to see the array
	   cs2[][] that gets created, just change that 0 two lines back
	   to a 1 and recompile */
	for (c=0; c<NCLL; c++) {
		printf("cell %2d: sets ", c);
		for (s=0; s<NGRP; s++) {
			printf("%3d", c2s[c][s]);
		}
		printf("\n");
	}
	printf("\n");
#endif
	return;
}

/* find the row number a cell is in, counting from 1
*/
int
rownum(int c) {
	return 1 + (c/(NDIM*NDIM));
}

/* find the column number a cell is in, counting from 1
*/
int
colnum(int c) {
	return 1 + (c%(NDIM*NDIM));
}

/* find the minor square number a cell is in, counting from 1
*/
int
sqrnum(int c) {
	return 1 + 3*(c/NSET) + (c/NDIM)%NDIM;
}

/* If you wish to add further #defines, put them below this comment,
   then prototypes for the functions that you add

   The only thing you should alter above this line is to complete the
   Authorship Declaration 
*/


/****************************************************************/
#define UNKNOWN 0
#define ROW_THRESHOLD 8
#define COL_THRESHOLD 17
#define COL_SEP '|'
#define ROW_SEP "------+-------+------"
#define EMPTY '.'
#define NO_VIOLATIONS 0
#define MAX_INSTANCES 1

int read_sudoku(int sudoku[]);
void print_sudoku(int sudoku[], int unknowns);
int grid_check(int sudoku[]);
void zero_array(int A[], int n);
void set_type(int set_num);
void strategy1(int sudoku[], int* unknowns);
void copy_sudoku(int original[], int copy[]);

/****************************************************************/

/* main program controls all the action
*/
int
main(int argc, char *argv[]) {
	int sudoku[NCLL], unknowns;

	fill_c2s();
	unknowns = read_sudoku(sudoku);
	print_sudoku(sudoku, unknowns);
	
	if (grid_check(sudoku)==NO_VIOLATIONS) {
		strategy1(sudoku, &unknowns);

		/* print out the final version of the soduku */
		if (unknowns==0) {
			print_sudoku(sudoku, unknowns);
			printf("\nta daa!!!\n");
		} else {
			print_sudoku(sudoku, unknowns);
		}
	}
	/* Algorithms are fun!!! */
	return 0;
}

/****************************************************************/
/* read input sudoku and count number of unknown cells */
int read_sudoku(int sudoku[]) {
	int cell, val, unknowns=0;

	for (cell=0; cell<NCLL; cell++) {
		scanf("%d", &val);
		if (val==UNKNOWN) {
			unknowns++;
		}
		sudoku[cell] = val;
	}
	return unknowns;
}

/* print out a neatly-formatted representation of the input sudoku and a line 
indicating the number of unknowns cells */
void print_sudoku(int sudoku[], int unknowns) {
	int cell;

	printf("\n");
	for (cell=0; cell<NCLL; cell++) {
		
		/* print row sperators/newline char if necessary */
		if (cell%(NDIG*NDIM)==0 && cell!=0) {
			printf("\n%s\n", ROW_SEP);
		} else if (cell%NDIG==0 && cell!=0) {
			printf("\n");
		}
		/* print column seperators if necessary */
		if (cell%NDIM==0 && cell%NDIG!=0) {
			printf(" %c", COL_SEP);
		} 
		/* print cells */
		if (sudoku[cell]==UNKNOWN && colnum(cell)==1) {
			printf("%c", EMPTY);
		} else if (sudoku[cell]==UNKNOWN) {
			printf(" %c", EMPTY);
		} else if (colnum(cell)==1) {
			printf("%d", sudoku[cell]);
		} else {
			printf("%2d", sudoku[cell]);
		}
	}
	printf("\n\n%2d cells are unknown\n", unknowns);
}

/* checks the input grid for mistakes, and report any errors */
int grid_check(int sudoku[]) {
	int set, cell, entry, violations=0, set_violation=0, unique_sets=0;
	int check_array[NDIG]={0};

	/* count occurrences of each number for each set */
	for (set=0; set<NSET; set++) {
		for (cell=0; cell<NDIG; cell++) {
			entry = sudoku[s2c[set][cell]];
			if (entry!=UNKNOWN) {
				check_array[entry-1]++;
			}
		}
		/* count instances of set violations and total violations and print 
		the violation message */
		for (cell=0; cell<NDIG; cell++) {
			if (check_array[cell]>MAX_INSTANCES) {
				violations ++;
				set_violation=1;
				if (violations == 1) {
					printf("\n");
				}
				printf("set %2d ", set);
				set_type(set);
				printf(": %d instances of %d\n", check_array[cell], cell+1);
			}
		}
		/* count number of different sets that have violation and renew 
		check_array for next set */
		if (set_violation==1) {
			unique_sets++;
			set_violation = 0;
		}
		zero_array(check_array, NDIG);
	}
	/* print the number of violations if there's any */
	if (violations != 0) {
		printf("\n%d different sets have violations\n", unique_sets);
		printf("%d violations in total\n", violations);
	}
	return violations;
}

/* sets all elements in the array to zero */
void zero_array(int A[], int n) {
	int i;
	for (i=0; i<n; i++) {
			A[i]=0;
		}
}

/* returns the row/column/square number of the given set number */
void set_type(int set_num) {
	int row_num, col_num, sqr_num;

	if (set_num<=ROW_THRESHOLD) {
		row_num = set_num + 1;
		printf("(row %d)", row_num);
	} else if (set_num > ROW_THRESHOLD && set_num <= COL_THRESHOLD) {
		col_num = set_num - ROW_THRESHOLD;
		printf("(col %d)", col_num);
	} else {
		sqr_num = set_num - COL_THRESHOLD;
		printf("(sqr %d)", sqr_num);
	}
}

/* prints the missing number for each unknown cell if doable */
void strategy1(int sudoku[], int* unknowns) {
	int sudoku_copy[NCLL], first_attempt=1, initial_unknowns=*unknowns;
	int cell, s, i, set, undetermined, missing_num, entry, heading=1;
	int nums_taken[NDIG]={0};

	/* all changes to the sudoku are saved to a copy */
	copy_sudoku(sudoku, sudoku_copy);

	/* apply strategy 1 until no more unknown cells can be resolved */
	while (first_attempt==1 || *unknowns<initial_unknowns) {
		initial_unknowns = *unknowns;
		heading = 1;

		/* analyse each unknown cell and find all existing numbers */
		for (cell=0; cell<NCLL; cell++) {
			if (sudoku[cell]==UNKNOWN) {
				undetermined = 0;
				for (s=0; s<NGRP; s++) {
					set = c2s[cell][s];
					for (i=0; i<NDIG; i++) {
						if (sudoku[s2c[set][i]]!=UNKNOWN) {
							entry = sudoku[s2c[set][i]];
							nums_taken[entry-1] = entry;
						}
					} 
				}
				/* determine possible number for the unknown cell */
				for (i=0; i<NDIG; i++) {
					if (nums_taken[i]==0) {
						undetermined ++;
						missing_num = i + 1;
					}
				}
				/* print out the missing number if there is only one possible 
				value for the unknown cell */
				if (undetermined==1) {
					if (heading==1) {
						printf("\nstrategy one\n");
						heading = 0;
					}
					sudoku_copy[cell] = missing_num;
					printf("row %d col %d must be %d\n", rownum(cell), 
					colnum(cell), sudoku_copy[cell]);
					*unknowns = *unknowns - 1;
				}
				zero_array(nums_taken, NDIG);
			}
		}
		/* update the sudoku */
		copy_sudoku(sudoku_copy, sudoku);
		first_attempt = 0;
	}
}

/* copy all the entries in the original sudoku to the other sudoku */
void copy_sudoku(int original[], int copy[]) {
	int c;
	for (c=0; c<NCLL; c++) {
		copy[c] = original[c];
	}
}


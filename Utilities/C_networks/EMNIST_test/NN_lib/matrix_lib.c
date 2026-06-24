
#include <stdlib.h>
#include <stdio.h>

#include "matrix_lib.h"
#include "NN_lib_debug.h"

/******************************************************************
*  Function: matrix_init
*
*  Purpose: Initialize the maxtrix, allocating it into dynamic
*           memory random values.
*
******************************************************************/

Matrix matrix_init(unsigned int row, unsigned int col){
	
	Matrix m;

	//Check row and col value
	if((row == 0) || (col == 0)){
		DEBUG_MATRIX_PRINTF("ERROR: Matrix dimensions not valid r:%d c:%d \n", row, col);
		return matrix_error();
	}

	//Allocate the matrix in memory
	m.data = (float*)malloc(sizeof(float)*row*col);
	if(m.data == NULL){
		DEBUG_MATRIX_PRINTF("ERROR: Matrix allocating memory malloc() has failed \n");
		return matrix_error();
	}
	
	//Write the matrix column and rows
	m.row = row;
	m.col = col;
	
	return m;

}

/******************************************************************
*  Function: matrix_rand
*
*  Purpose: Initialize the maxtrix, allocating it into dynamic
*           memory random values included between min and max.
*
******************************************************************/

Matrix matrix_rand(unsigned int row, unsigned int col, float min, float max){

	Matrix m = matrix_init(row, col);
	float rand_val = (float)rand()/RAND_MAX;

	for(unsigned long int i=0; i<(m.row*m.col); i++)
		m.data[i] = (rand_val*(max - min)) + min;;

	return m;
	
}

/******************************************************************
*  Function: matrix_identity
*
*  Purpose: Initialize the maxtrix, allocating it into dynamic
*           memory the identity matrix.
*
******************************************************************/

Matrix matrix_identity(unsigned int dim){

	Matrix m = matrix_init(dim, dim);

	for(unsigned int c=0; c<m.col; c++)
		for(unsigned int r=0; r<m.row; r++)
			m.data[c*m.row + r] = (c == r) ? 1.00f : 0.00f;	

	return m;

}

/******************************************************************
*  Function: matrix_fill
*
*  Purpose: Initialize the maxtrix, allocating it into dynamic
*           memory a value (val) filled matrix.
*
******************************************************************/

Matrix matrix_fill(unsigned int row, unsigned int col, float val){

	Matrix m = matrix_init(row, col);

	for(unsigned long int i=0; i<(m.row*m.col); i++)
		m.data[i] = val;	

	return m;

}

/******************************************************************
*  Function: matrix_null
*
*  Purpose: Initialize the maxtrix, allocating it into dynamic
*           memory a zero filled matrix.
*
******************************************************************/

Matrix matrix_null(unsigned int row, unsigned int col){

	Matrix m = matrix_init(row, col);

	for(unsigned long int i=0; i<(m.row*m.col); i++)
		m.data[i] = 0.00f;	

	return m;

}

/******************************************************************
*  Function: matrix_assign
*
*  Purpose: Copy the content of Matrix b into Matrix a.
*
******************************************************************/

void matrix_assign(Matrix *a, const Matrix b){

	matrix_free(a);
	*a = matrix_init(b.row, b.col);

	for(unsigned long int i=0; i<((*a).row*(*a).col); i++)
		(*a).data[i] = b.data[i];

}

/******************************************************************
*  Function: matrix_copy_data
*
*  Purpose: Copy the data of Matrix b into Matrix a.
*			if Matrix a have different dimensions of Matrix b 
*			return 0, otherwise return 1
*
******************************************************************/

int matrix_copy_data(Matrix *a, const Matrix b){

	if(((*a).row != b.row) || ((*a).col != b.col)){
		DEBUG_MATRIX_PRINTF("ERROR: Matrix dimensions not equals \n");
		DEBUG_MATRIX_PRINTF("a.r:%d a.c:%d / b.r:%d b.c:%d \n", (*a).row, (*a).col, b.row, b.col);
		return 0;		//Return error
	}

	for(unsigned long int i=0; i<(b.row*b.col); i++)
		(*a).data[i] = b.data[i];
	
	return 1;		//Return success
	
}

/******************************************************************
*  Function: matrix_multiply
*
*  Purpose: Multply the matrix a and b and put the result into
*			matrix result.
*
******************************************************************/

int matrix_multiply(Matrix *a, Matrix *b, Matrix *result){

	//Check if multiplication can be done
	if((*a).col != (*b).row){
		DEBUG_MATRIX_PRINTF("ERROR: Dimensions do not allow matrix product a.c:%d b.r:%d \n", (*a).col, (*b).row);
		return 0;		//Error dimensions
	}

	//Compute the resul matrix dimsnsions
	unsigned int r_row_n, r_col_n;
	r_row_n = (*a).row;
	r_col_n = (*b).col;

	//Generate the result matrix (if is not already generated)
	matrix_free(result);
	(*result) = matrix_init(r_row_n, r_col_n);
	if(matrix_valid(result) == 0)
		return 0;	//Error generating resulting matrix

	//Make the multiplication
	unsigned int a_col_b_row_n = (*a).col;
	for(unsigned int r=0; r<(*a).row; r++){			//row index
		for(unsigned int c=0; c<(*b).col; c++){		//column index

			//Reset the value before multiplication
			(*result).data[c*r_row_n + r] = 0;
			for(unsigned int i=0; i<a_col_b_row_n; i++){

				//Matrix indexing syntax
				//m[ column * row_length + row ] -> m[row][column]

				(*result).data[c*r_row_n + r] += 
				((*a).data[i*(*a).row + r]) * ((*b).data[c*(*b).row + i]);

			}
		}
	}

	return 1;	//Exit success

}

/******************************************************************
*  Function: matrix_sum
*
*  Purpose: Multply the matrix a and b and put the result into
*			matrix result.
*
******************************************************************/

int matrix_sum(Matrix *a, Matrix *b, Matrix *result){

	//Check if sum can be done
	if(((*a).col != (*b).col) || ((*a).row != (*b).row)){
		DEBUG_MATRIX_PRINTF("ERROR: Dimensions do not allow matrix sum \n");
		DEBUG_MATRIX_PRINTF("a.r:%d a.c:%d b.r:%d b.c:%d \n", (*a).row, (*a).col, (*b).row, (*b).col);
		return 0;		//Error dimensions
	}

	//Compute the resul matrix dimsnsions
	unsigned int r_row_n, r_col_n;
	r_row_n = (*a).row;
	r_col_n = (*a).col;

	//Generate the result matrix (if is not already generated)
	matrix_free(result);
	(*result) = matrix_init(r_row_n, r_col_n);
	if(matrix_valid(result) == 0)
		return 0;	//Error generating resulting matrix

	//Make the sum
	for(unsigned long int i=0; i<(r_row_n*r_col_n); i++)
		(*result).data[i] = (*a).data[i] + (*b).data[i];

	return 1;	//Exit success

}

/******************************************************************
*  Function: matrix_transpose
*
*  Purpose: Transform m in his transposed matrix.
*
******************************************************************/

void matrix_transpose(Matrix *m){

	Matrix m_trans = matrix_init((*m).col, (*m).row);

	for(unsigned int r=0; r<(*m).row; r++)			//row index
		for(unsigned int c=0; c<(*m).col; c++)		//column index

			//Matrix indexing syntax
			//m[ column * row_length + row ] -> m[row][column]
 
			(m_trans.data[r*m_trans.row + c]) = ((*m).data[c*(*m).row + r]);


	matrix_free(m);
	(*m) = m_trans;

}

/******************************************************************
*  Function: matrix_valid
*
*  Purpose: Check the matrix is different from matrix_error().
*
******************************************************************/

int matrix_valid(Matrix *m){
	if(((*m).col == 0) && ((*m).row == 0) && ((*m).data == NULL))
		return 0;	//Matrix not valid
	return 1;		//Matrix valid
}

/******************************************************************
*  Function: matrix_compare
*
*  Purpose: Check if matrix a and matrix b are equal.
*
******************************************************************/

int matrix_compare(Matrix *a, Matrix *b){

	if(((*a).row != (*b).row) || ((*a).col != (*b).col))
		return 0;		//Matrix different
	
	for(unsigned long int i=0; i<((*a).row*(*a).col); i++)
		if((*a).data[i] != (*b).data[i])
			return 0;		//Matrix different


	return 1;		//Matrix equals

}

/******************************************************************
*  Function: matrix_print
*
*  Purpose: Print the values inside matrix.
*
******************************************************************/

void matrix_print(Matrix *m){

	printf("Marix rows: %d \nMatrix column: %d \n", (*m).row, (*m).col);
	for(unsigned int c=0; c<(*m).col; c++){
		for(unsigned int r=0; r<(*m).row; r++){

			//Matrix indexing syntax
			//m[ column * row_length + row ] -> m[row][column]

			printf("%f ", (*m).data[c*(*m).row + r]);

		}
		printf("\n");
	}
	printf("\n");

}

/******************************************************************
*  Function: matrix_init
*
*  Purpose: Deallocate the matrix from dynamic memory.
*
******************************************************************/

void matrix_free(Matrix *m){

	free((*m).data);

}
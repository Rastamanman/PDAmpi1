// mpitest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "mpi.h"
#include <stdio.h>

using namespace std;

#define NRVect 4


int main(int argc, char *argv[])
{
	int vect[NRVect];
	for (int i = 0; i < NRVect; i++)
	{
		cin >> vect[i];
	}

	MPI_Request req[NRVect];
	MPI_Status status;
	int rnk,sz;
	int idk;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rnk);
	MPI_Comm_size(MPI_COMM_WORLD, &sz);

	cout << "size: " << sz << endl;

	int part = NRVect / (sz - 1);
	if (rnk < 0)
	{
		cout << "Problema" << endl;
		//MPI_Abort(MPI_COMM_WORLD, rnk);
	}
	else if (rnk > 0)
	{
		//worker
		int start = (rnk - 1) * part;
		int fin = rnk * part;
		int suma = 0;
		for (int i = start; i < fin; i++)
		{
			suma += vect[i];
		}
		MPI_Recv(&idk, 1, MPI_INT, 0, 1234, MPI_COMM_WORLD, &status);
		MPI_Send(&suma, 1, MPI_INT, 0, 4321, MPI_COMM_WORLD);
	}
	else
	{
		//master
		int sum = 0;
		for (int i = 1; i <= sz; i++)
		{
			MPI_Send(&idk, i, MPI_INT, i, 1234, MPI_COMM_WORLD);
			int tempsum = 0;
			MPI_Recv(&tempsum, 1, MPI_INT,i, 4321, MPI_COMM_WORLD, &status);
			sum += tempsum;
		}

		cout << "Suma vectorului este: " << sum << endl;
	}
	MPI_Finalize();
	cin >> sz;
    return 0;
}


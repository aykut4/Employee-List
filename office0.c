// Author: Aykut Sahin
// sahinayk@fit.cvut.cz
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct TCar
{
  struct TCar              * m_Next;
  char                     * m_Model;
} TCAR;

typedef struct TEmployee
{
  struct TEmployee         * m_Next;
  struct TCar              * m_Car;
  char                     * m_Name;
} TEMPLOYEE;

typedef struct TOffice
{
  TEMPLOYEE                * m_Emp;
  TCAR                     * m_Car;
} TOFFICE;

TOFFICE* initOffice ()
{
	TOFFICE* ptOffice = (TOFFICE*)malloc(sizeof(TOFFICE));
	ptOffice->m_Emp = NULL;
	ptOffice->m_Car = NULL;
	return ptOffice;
}

TEMPLOYEE* initTemployee ()
{
	TEMPLOYEE* ptEmp = (TEMPLOYEE*)malloc(sizeof(TEMPLOYEE));
	return ptEmp;
}

void addEmployee (TOFFICE* office, const char* name)
{
	TEMPLOYEE* newEmp = initTemployee();
	newEmp->m_Next = office->m_Emp;
	newEmp->m_Name = strdup(name);
	newEmp->m_Car = NULL;
	office->m_Emp = newEmp;
}

TCAR* initTcar ()
{
	TCAR* ptCar = (TCAR*)malloc(sizeof(TCAR));
	return ptCar;
}

void addCar (TOFFICE* office, const char* model)
{
	TCAR* newCar = initTcar();
	newCar->m_Next = office->m_Car;
	newCar->m_Model = strdup(model);
	office->m_Car = newCar;
}

void freeOffice (TOFFICE* office)
{
	TOFFICE* tmp = (TOFFICE*)malloc(sizeof(TOFFICE));

	while (office->m_Emp)
	{
		tmp->m_Emp = office->m_Emp->m_Next;
		free(office->m_Emp->m_Name);
		free(office->m_Emp);
		office->m_Emp = tmp->m_Emp;
	}

	while (office->m_Car)
	{
		tmp->m_Car = office->m_Car->m_Next;
		free(office->m_Car->m_Model);
		free(office->m_Car);
		office->m_Car = tmp->m_Car;
	}
	free(tmp);
	free(office);
}

TOFFICE* cloneOffice (TOFFICE* office)
{
	TOFFICE* helper = initOffice();
	TOFFICE* helperv2 = initOffice();

	helper->m_Emp = office->m_Emp;
	helper->m_Car = office->m_Car;

	helperv2->m_Emp = helper->m_Emp;
	helperv2->m_Car = helper->m_Car;

	TCAR* cloneCar = NULL;

	while (helper->m_Car)
	{
		cloneCar = (TCAR*)malloc(sizeof(TCAR));
		cloneCar->m_Model = strdup(helper->m_Car->m_Model);
		cloneCar->m_Next = helper->m_Car->m_Next;
		helper->m_Car->m_Next = cloneCar;

		helper->m_Car = helper->m_Car->m_Next->m_Next;
	}

	TEMPLOYEE* cloneEmp = NULL;

	while (helper->m_Emp)
	{
		cloneEmp = (TEMPLOYEE*)malloc(sizeof(TEMPLOYEE));
		cloneEmp->m_Name = strdup(helper->m_Emp->m_Name);
		if (helper->m_Emp->m_Car != NULL)
		{
			cloneEmp->m_Car = helper->m_Emp->m_Car->m_Next;
		}
		else
		{
			cloneEmp->m_Car = NULL;
		}
		cloneEmp->m_Next = helper->m_Emp->m_Next;
		helper->m_Emp->m_Next = cloneEmp;

		helper->m_Emp = helper->m_Emp->m_Next->m_Next;
	}
	helper->m_Emp = helperv2->m_Emp;
	helper->m_Car = helperv2->m_Car;
	free(helperv2);


	TOFFICE* cloneOffice = initOffice();
	TOFFICE* cloneOfficeHelper = initOffice();

	cloneOffice->m_Emp = helper->m_Emp->m_Next;
	cloneOfficeHelper->m_Emp = cloneOffice->m_Emp;
	while (helper->m_Emp)
	{
		helper->m_Emp->m_Next = helper->m_Emp->m_Next->m_Next;
		if (helper->m_Emp->m_Next != NULL)
		{
			cloneOffice->m_Emp->m_Next = helper->m_Emp->m_Next->m_Next;
		}
		else
		{
			cloneOffice->m_Emp->m_Next = NULL;
		}
		helper->m_Emp = helper->m_Emp->m_Next;
		cloneOffice->m_Emp = cloneOffice->m_Emp->m_Next;
	}
	cloneOffice->m_Emp = cloneOfficeHelper->m_Emp;

	cloneOffice->m_Car= helper->m_Car->m_Next;
	cloneOfficeHelper->m_Car = cloneOffice->m_Car;
	while (helper->m_Car)
	{
		helper->m_Car->m_Next = helper->m_Car->m_Next->m_Next;
		if (helper->m_Car->m_Next != NULL)
		{
			cloneOffice->m_Car->m_Next = helper->m_Car->m_Next->m_Next;
		}
		else
		{
			cloneOffice->m_Car->m_Next = NULL;
		}
		helper->m_Car = helper->m_Car->m_Next;
		cloneOffice->m_Car = cloneOffice->m_Car->m_Next;
	}
	cloneOffice->m_Car = cloneOfficeHelper->m_Car;

	free(cloneOfficeHelper);
	free(helper);
	return cloneOffice;
}

int main ( int argc, char * argv [] )
{
  TOFFICE * a, *b;
  char tmp[100];

  assert ( sizeof ( TOFFICE ) == 2 * sizeof ( void * ) );
  assert ( sizeof ( TEMPLOYEE ) == 3 * sizeof ( void * ) );
  assert ( sizeof ( TCAR ) == 2 * sizeof ( void * ) );
  a = initOffice ();
  addEmployee ( a, "Peter" );
  addEmployee ( a, "John" );
  addEmployee ( a, "Joe" );
  addEmployee ( a, "Maria" );
  addCar ( a, "Skoda Octavia" );
  addCar ( a, "VW Golf" );
  a -> m_Emp -> m_Car = a -> m_Car;
  a -> m_Emp -> m_Next -> m_Next -> m_Car = a -> m_Car -> m_Next;
  a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Car = a -> m_Car;
  assert ( a -> m_Emp
           && ! strcmp ( a -> m_Emp -> m_Name, "Maria" )
           && a -> m_Emp -> m_Car == a -> m_Car );
  assert ( a -> m_Emp -> m_Next
           && ! strcmp ( a -> m_Emp -> m_Next -> m_Name, "Joe" )
           && a -> m_Emp -> m_Next -> m_Car == NULL );
  assert ( a -> m_Emp -> m_Next -> m_Next
           && ! strcmp ( a -> m_Emp -> m_Next -> m_Next -> m_Name, "John" )
           && a -> m_Emp -> m_Next -> m_Next -> m_Car == a -> m_Car -> m_Next );
  assert ( a -> m_Emp -> m_Next -> m_Next -> m_Next
           && ! strcmp ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
           && a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Car == a -> m_Car );
  assert ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  assert ( a -> m_Car
           && ! strcmp ( a -> m_Car -> m_Model, "VW Golf" ) );
  assert ( a -> m_Car -> m_Next
           && ! strcmp ( a -> m_Car -> m_Next -> m_Model, "Skoda Octavia" ) );
  assert ( a -> m_Car -> m_Next -> m_Next == NULL );
  b = cloneOffice ( a );
  strncpy ( tmp, "Moe", sizeof ( tmp ) );
  addEmployee ( a, tmp );
  strncpy ( tmp, "Victoria", sizeof ( tmp ) );
  addEmployee ( a, tmp );
  strncpy ( tmp, "Peter", sizeof ( tmp ) );
  addEmployee ( a, tmp );
  strncpy ( tmp, "Citroen C4", sizeof ( tmp ) );
  addCar ( a, tmp );
  b -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Car = b -> m_Car -> m_Next -> m_Next;
  assert ( a -> m_Emp
           && ! strcmp ( a -> m_Emp -> m_Name, "Peter" )
           && a -> m_Emp -> m_Car == NULL );
  assert ( a -> m_Emp -> m_Next
           && ! strcmp ( a -> m_Emp -> m_Next -> m_Name, "Victoria" )
           && a -> m_Emp -> m_Next -> m_Car == NULL );
  assert ( a -> m_Emp -> m_Next -> m_Next
           && ! strcmp ( a -> m_Emp -> m_Next -> m_Next -> m_Name, "Moe" )
           && a -> m_Emp -> m_Next -> m_Next -> m_Car == NULL );
  assert ( a -> m_Emp -> m_Next -> m_Next -> m_Next
           && ! strcmp ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Name, "Maria" )
           && a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Car == a -> m_Car -> m_Next );
  assert ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "Joe" )
           && a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next -> m_Car == NULL );
  assert ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "John" )
           && a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Car == a -> m_Car -> m_Next -> m_Next );
  assert ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
           && a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Car == a -> m_Car -> m_Next );
  assert ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  assert ( a -> m_Car
           && ! strcmp ( a -> m_Car -> m_Model, "Citroen C4" ) );
  assert ( a -> m_Car -> m_Next
           && ! strcmp ( a -> m_Car -> m_Next -> m_Model, "VW Golf" ) );
  assert ( a -> m_Car -> m_Next -> m_Next
           && ! strcmp ( a -> m_Car -> m_Next -> m_Next -> m_Model, "Skoda Octavia" ) );
  assert ( a -> m_Car -> m_Next -> m_Next -> m_Next == NULL );
  assert ( b -> m_Emp
           && ! strcmp ( b -> m_Emp -> m_Name, "Maria" )
           && b -> m_Emp -> m_Car == b -> m_Car );
  assert ( b -> m_Emp -> m_Next
           && ! strcmp ( b -> m_Emp -> m_Next -> m_Name, "Joe" )
           && b -> m_Emp -> m_Next -> m_Car == NULL );
  assert ( b -> m_Emp -> m_Next -> m_Next
           && ! strcmp ( b -> m_Emp -> m_Next -> m_Next -> m_Name, "John" )
           && b -> m_Emp -> m_Next -> m_Next -> m_Car == b -> m_Car -> m_Next );
  assert ( b -> m_Emp -> m_Next -> m_Next -> m_Next
           && ! strcmp ( b -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
           && b -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Car == NULL );
  assert ( b -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  assert ( b -> m_Car
           && ! strcmp ( b -> m_Car -> m_Model, "VW Golf" ) );
  assert ( b -> m_Car -> m_Next
           && ! strcmp ( b -> m_Car -> m_Next -> m_Model, "Skoda Octavia" ) );
  assert ( b -> m_Car -> m_Next -> m_Next == NULL );
  freeOffice ( a );
  freeOffice ( b );
  return 0;
}

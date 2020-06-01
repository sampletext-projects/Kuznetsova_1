//можно включать любую из этих
#include <stdio.h>
#include <cstdio>
//----

#include <conio.h>

//можно включать любую из этих
#include <stdlib.h>
#include <cstdlib>
//----

#include <cstring>
#include <tchar.h>

#include <crtdbg.h> // определение утечки памяти

//Эта штука нужна только для новых версий студии
//getch обычный отсутствует, поэтому настраиваем _getch на притворство обычным getch
#ifdef _MSC_VER
#define getch() _getch()
#endif

typedef enum machines
{
	MSpinner = 1,
	MPuller = 2,
	MBeater = 3
} Machines;

typedef struct
{
	Machines type;
	double frequency;
	double power;
	double time_h;
	char name[20];
} SpinnerMachine;

typedef struct
{
	Machines type;
	double ropeLength;
	double power;
	double time_h;
	char name[20];
} PullerMachine;

typedef struct
{
	Machines type;
	double weight;
	double power;
	double time_h;
	char name[20];
} BeaterMachine;

SpinnerMachine* CreateSpinnerMachine()
{
	double frequency;
	double power;
	double time_h;
	char name[20];
	printf("Enter frequency: ");
	scanf("%lf", &frequency);
	printf("Enter power: ");
	scanf("%lf", &power);
	printf("Enter time_h: ");
	scanf("%lf", &time_h);
	printf("Enter name: ");
	scanf("%s", name);
	if (frequency < 0)
	{
		return NULL;
	}
	if (power < 0)
	{
		return NULL;
	}
	if (time_h < 0)
	{
		return NULL;
	}
	if (*name == '\0')
	{
		return NULL;
	}
	SpinnerMachine* machine = (SpinnerMachine*)malloc(sizeof(SpinnerMachine));
	if (machine == NULL)
	{
		return NULL;
	}
	machine->type = machines::MSpinner;
	machine->frequency = frequency;
	machine->power = power;
	machine->time_h = time_h;
	memcpy(machine->name, name, sizeof(char) * 20);
	return machine;
}

PullerMachine* CreatePullerMachine()
{
	double ropeLength;
	double power;
	double time_h;
	char name[20];
	printf("Enter ropeLength: ");
	scanf("%lf", &ropeLength);
	printf("Enter power: ");
	scanf("%lf", &power);
	printf("Enter time_h: ");
	scanf("%lf", &time_h);
	printf("Enter name: ");
	scanf("%s", name);
	if (ropeLength < 0)
	{
		return NULL;
	}
	if (power < 0)
	{
		return NULL;
	}
	if (time_h < 0)
	{
		return NULL;
	}
	if (*name == '\0')
	{
		return NULL;
	}
	PullerMachine* machine = (PullerMachine*)malloc(sizeof(PullerMachine));
	if (machine == NULL)
	{
		return NULL;
	}
	machine->type = machines::MSpinner;
	machine->ropeLength = ropeLength;
	machine->power = power;
	machine->time_h = time_h;
	memcpy(machine->name, name, sizeof(char) * 20);
	return machine;
}

BeaterMachine* CreateBeaterMachine()
{
	double weight;
	double power;
	double time_h;
	char name[20];
	printf("Enter weight: ");
	scanf("%lf", &weight);
	printf("Enter power: ");
	scanf("%lf", &power);
	printf("Enter time_h: ");
	scanf("%lf", &time_h);
	printf("Enter name: ");
	scanf("%s", name);
	if (weight < 0)
	{
		return NULL;
	}
	if (power < 0)
	{
		return NULL;
	}
	if (time_h < 0)
	{
		return NULL;
	}
	if (*name == '\0')
	{
		return NULL;
	}
	BeaterMachine* machine = (BeaterMachine*)malloc(sizeof(BeaterMachine));
	if (machine == NULL)
	{
		return NULL;
	}
	machine->type = machines::MSpinner;
	machine->weight = weight;
	machine->power = power;
	machine->time_h = time_h;
	memcpy(machine->name, name, sizeof(char) * 20);
	return machine;
}

void RemoveMachines(void** ppMachines, int count)
{
	int counter = 0;
	void* m = ppMachines[0];
	while (m != NULL)
	{
		Machines type = *((Machines*)m);
		switch (type)
		{
		case MSpinner:
			{
				free((SpinnerMachine*)m);
				break;
			}
		case MPuller:
			{
				free((PullerMachine*)m);
				break;
			}
		case MBeater:
			{
				free((BeaterMachine*)m);
				break;
			}
		default:
			printf("Error in RemoveMachines\n");
			return;
		}
		ppMachines[counter] = NULL;
		counter++;
		if (counter == count)
		{
			return;
		}
		m = ppMachines[counter];
	}
}

int AddMachines(void** ppMachines)
{
	if (ppMachines[0] != NULL)
	{
		RemoveMachines(ppMachines, 4);
	}
	int counter = 0;
	bool quit = false;
	while (!quit)
	{
		if (counter > 3)
		{
			return counter;
		}
		printf("Enter machine kind: \n");
		printf("1. SpinnerMachine: \n");
		printf("2. PullerMachine: \n");
		printf("3. BeaterMachine: \n");
		printf("e. Exit: \n");
		int key = getch();
		switch (key)
		{
		case '1':
			{
				SpinnerMachine* m = CreateSpinnerMachine();
				if (m != NULL)
				{
					ppMachines[counter] = m;
					counter++;
				}
				break;
			}
		case '2':
			{
				PullerMachine* m = CreatePullerMachine();
				if (m != NULL)
				{
					ppMachines[counter] = m;
					counter++;
				}
				break;
			}
		case '3':
			{
				BeaterMachine* m = CreateBeaterMachine();
				if (m != NULL)
				{
					ppMachines[counter] = m;
					counter++;
				}
				break;
			}
		case 'e':
		case 'E':
			{
				printf("%d machines were created.\n", counter);
				return counter;
				break;
			}
		default:
			{
				printf("Enter a correct number. Try again or exit.\n");
			}
		}

		printf("%d machines were created.\n", counter);
		return counter;
	}
}

//C - consumption - потребление
double GetMachinesDailyC(void** ppMachines, int count)
{
	double dailyC = 0;
	for (int i = 0; i < count; i++)
	{
		void* p = ppMachines[i];
		Machines type = *((Machines*)p);
		switch (type)
		{
		case MSpinner:
			{
				SpinnerMachine* m = (SpinnerMachine*)p;
				dailyC += m->power * m->time_h;
				break;
			}
		case MPuller:
			{
				PullerMachine* m = (PullerMachine*)p;
				dailyC += m->power * m->time_h;
				break;
			}
		case MBeater:
			{
				BeaterMachine* m = (BeaterMachine*)p;
				dailyC += m->power * m->time_h;
				break;
			}
		default:
			printf("Error in calculation dailyC\n");
			return 0;
		}
	}
	return dailyC;
}

//C - consumption - потребление
double GetMachinesTotalC(void** ppMachines, int count)
{
	double total = 0;
	for (int i = 0; i < count; i++)
	{
		void* p = ppMachines[i];
		Machines type = *((Machines*)p);
		switch (type)
		{
		case MSpinner:
			{
				SpinnerMachine* m = (SpinnerMachine*)p;
				total += m->power;
				break;
			}
		case MPuller:
			{
				PullerMachine* m = (PullerMachine*)p;
				total += m->power;
				break;
			}
		case MBeater:
			{
				BeaterMachine* m = (BeaterMachine*)p;
				total += m->power;
				break;
			}
		default:
			printf("Error in calculation TotalC\n");
			return 0;
		}
	}
	return total;
}

int main()
{
	void** ppMachines = new void*[4]{NULL, NULL, NULL,NULL};
	int count = 0;
	bool quit = false;
	while (!quit)
	{
		printf("Enter machine kind: \n");
		printf("1. Create Machines: \n");
		printf("2. Get Daily Consumption: \n");
		printf("3. Get Total Consumption: \n");
		printf("e. Exit: \n");
		int key = getch();
		switch (key)
		{
		case '1':
			{
				count = AddMachines(ppMachines);
				break;
			}
		case '2':
			{
				double c = GetMachinesDailyC(ppMachines, count);
				printf("Daily Consumption: %lf\n", c);
				break;
			}
		case '3':
			{
				double c = GetMachinesTotalC(ppMachines, count);
				printf("Total Consumption: %lf\n", c);
				break;
			}
		case 'e':
		case 'E':
			{
				quit = true;
				break;
			}
		default:
			{
				printf("Enter a correct number. Try again or exit.\n");
			}
		}
	}
	RemoveMachines(ppMachines, count);
	delete[] ppMachines;
	_CrtDumpMemoryLeaks();
	return 0;
}

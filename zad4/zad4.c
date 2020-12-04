#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

typedef struct polinom* poz;
struct polinom 
{
	int koef;
	int eksp;
	poz next;
};

int Ispis(poz);
int Suma(poz, poz, poz);
int Produkt(poz, poz, poz);
int SortUnos(int, int, poz);

int main()
{
	char ime[100];
	struct polinom head1, head2, zbroj, umnozak;
	head1.next = NULL;
	head2.next = NULL;
	zbroj.next = NULL;
	umnozak.next = NULL;
	
	printf("Unesi ime datoteke: \n");
	scanf("%s", ime);
	
	FILE* datoteka = fopen(ime, "r");
	if (!datoteka)
		printf("Krivo otvorena datoteka! \n");

	while (!feof(datoteka))
	{
		if (fgetc(datoteka) != '\n')
		{
			fscanf(datoteka, "%d %d", &head1.koef, &head1.eksp);
			SortUnos(head1.koef, head1.eksp, &head1);
		}
		else
		{
			while (!feof(datoteka))
			{
				fscanf(datoteka, "%d %d", &head2.koef, &head2.eksp);
				SortUnos(head2.koef, head2.eksp, &head2);
			}
		}
	}

	printf("\n Prvi polinom: \n");
	Ispis(&head1);
	printf("\n Drugi polinom: \n");
	Ispis(&head2);

	printf("\n Zbroj polinoma: \n");
	Suma(&head1, &head2, &zbroj);
	Ispis(&zbroj);

	printf("\n Umnozak polinoma: \n");
	Produkt(&head1, &head2, &umnozak);
	Ispis(&umnozak);

	return 0;
}

int Suma(poz p, poz q, poz r)
{
	p = p->next;
	q = q->next;

	while (p != NULL && q != NULL)
	{
		poz temp = (poz)malloc(sizeof(struct polinom));
		
		if (p->eksp == q->eksp)
		{
			temp->koef = p->koef + q->koef;
			if (temp != 0)
			{
				temp->eksp = p->eksp;
				SortUnos(temp->koef, temp->eksp, r);
			}
			p = p->next;
			q = q->next;
		}
		else if (p->eksp < q->eksp)
		{
			temp->koef = p->koef;
			temp->eksp = p->eksp;
			SortUnos(temp->koef, temp->eksp, r);

			p = p->next;
		}
		else
		{
			temp->koef= q->koef; 
			temp->eksp = q->eksp;
			SortUnos(temp->koef, temp->eksp, r);

			q = q->next;
		}
	}
	if (p == NULL)
	{
		while (q != NULL)
		{
			poz temp = (poz)malloc(sizeof(struct polinom));
			
			temp->koef = q->koef;
			temp->eksp = q->eksp;
			SortUnos(temp->koef, temp->eksp, r);

			q = q->next;
		}
	}
	if (q == NULL)
	{
		while (p != NULL)
		{
			poz temp = (poz)malloc(sizeof(struct polinom));

			temp->koef = p->koef;
			temp->eksp = p->eksp;
			SortUnos(temp->koef, temp->eksp, r);

			p = p->next;
		}
	}
	return 0;
}

int Produkt(poz p, poz q, poz r)
{
	p = p->next;
	q = q->next;

	poz temp, TEMP, x;
	TEMP = q;

	while (p != NULL)
	{
		while (q != NULL)
		{
			temp = (poz)malloc(sizeof(struct polinom));

			temp->koef = p->koef*q->koef;
			temp->eksp = p->eksp + q->eksp;
			if (temp->koef != 0)
				SortUnos(temp->koef, temp->eksp, r);
			q = q->next;
		}
		q = TEMP;
		p = p->next;
	}

	while (r->next != NULL)
	{
		if (r->eksp == r->next->eksp)
		{
			r->koef = r->koef + r->next->koef;
			x = r->next;
			r->next = x->next;
			free(x);
		}
		else
			r = r->next;
	}
	return 0;
}
int SortUnos(int x, int y, poz p)
{
	poz q;

	while (p->next != NULL && p->next->eksp < y)
		p = p->next;

	q = (poz)malloc(sizeof(struct polinom));
	q->eksp = y;
	q->koef = x;

	q->next = p->next;
	p->next = q;

	return 0;
}

int Ispis(poz p)
{
	p = p->next;
	if (p == NULL)
		printf("Lista je prazna! \n");
	printf(" koef \t eksp \n");
	while (p != NULL)
	{
		printf("  %d \t %d \n", p->koef, p->eksp);
		p = p->next;
	}
	return 0;
}
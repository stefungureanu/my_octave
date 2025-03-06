#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "matrices.h"

int main(void)
{	// i1, i2 folosite pentru indici/n si m, leak devine 1 cand o alocare pica
	// nr - 1 = index max, ok = nr matrici (verifica si existena matricelor)
	int i1, i2, leak = 0, nr = 0, ok = 0;
	int *sume = malloc(1 * sizeof(int));
	int *n_mat = malloc(1 * sizeof(int));
	int *m_mat = malloc(1 * sizeof(int));
	int ***v = malloc(1 * sizeof(int **));
	// Stiva pentru stdin
	char *a = malloc(2 * sizeof(char));
	if (!a || !v || !m_mat || !n_mat || !sume)
		leak = 1;
	do {
		// Alocare picata inainte sa intram
		if (leak)
			break;
		scanf("%s", a);
		if (a[0] == 'L') {
			// Creste nr de matrici, dim vectorilor si adaugam + citim matricea
			ok++;
			red_arr(&n_mat, &m_mat, &sume, ok, 1, &leak);
			red_mat(&v, ok, 1, &leak);
			scanf("%d%d", &i1, &i2);
			add_mat(i1, i2, v, n_mat, m_mat, &nr, 1, &leak);
		}
		if (a[0] == 'M' || a[0] == 'S') {
			scanf("%d%d", &i1, &i2);
			// Exista si se pot inmulti?
			if (multip_verif(nr, ok, n_mat, m_mat, i1, i2)) {
				// Ca la L, doar ca nu mai citim, ci o formam din v[i1],v[i2]
				ok++;
				red_arr(&n_mat, &m_mat, &sume, ok, 1, &leak);
				red_mat(&v, ok, 1, &leak);
				add_mat(n_mat[i1], m_mat[i2], v, n_mat, m_mat, &nr, 0, &leak);
				int i = nr - 1;
				// Modul de inmultire
				if (a[0] == 'M')
					mult(v[i1], v[i2], v[i], n_mat[i1], m_mat[i2], n_mat[i2]);
				else
					strassen(v[i1], v[i2], v[i], n_mat[i1], &leak);
			}
		}
		if (a[0] == 'D')
			dim(nr, ok, n_mat, m_mat);
		if (a[0] == 'P')
			print(nr, ok, v, n_mat, m_mat);
		if (a[0] == 'C')
			redim(nr, ok, v, n_mat, m_mat, &leak);
		if (a[0] == 'O') {
			// Intai updatam vectorul de sume
			sum_all(sume, v, n_mat, m_mat, nr);
			sort_mat(sume, v, n_mat, m_mat, nr);
		}
		if (a[0] == 'T')
			transp(nr, ok, v, n_mat, m_mat, &leak);
		if (a[0] == 'R')
			pow_mat(nr, ok, v, n_mat, m_mat, &leak);
		if (a[0] == 'F') {
			scanf("%d", &i1);
			if (exist(nr, ok, i1)) {
				rem_mat(nr, i1, v, n_mat, m_mat);
				// Micsoram vectorii
				red_arr(&n_mat, &m_mat, &sume, ok, 1, &leak);
				red_mat(&v, ok, 1, &leak);
				// Scadem indicele si nr de matrici
				nr--;
				ok--;
			} else {
				printf("No matrix with the given index\n");
			}
		}
		if (!strchr("LDPCMOTRFQS", a[0]))
			printf("Unrecognized command\n");
	} while (a[0] != 'Q' && !leak);
	// Eliberam toata memoria alocata dinamic
	clear_mem(v, sume, n_mat, m_mat, a, nr);
	if (leak) {
		fprintf(stderr, "Memory allocation failed\n");
		exit(-1);
	}
	return 0;
}

#include "matrices.h"

int exist(int total, int ok, int ind)
{
	if (ind < total && ok && ind >= 0)
		return 1;
	else
		return 0;
}

int **alloc_mat(int n, int m)
{	// Pointer to rows
	int **a = malloc(n * sizeof(int *));
	// No mem
	if (!a)
		return NULL;
	for (int i = 0; i < n; i++) {
		// M sized
		a[i] = malloc(m * sizeof(int));
		// No mem, clear all until now
		if (!a) {
			for (int j = i; j >= 0; j--)
				free(a[j]);
			free(a);
			return NULL;
		}
	}
	// Return alloc'd
	return a;
}

void free_mat(int **a, int n)
{
	// Delete one row at a time
	for (int i = 0; i < n; i++) {
		// If for some reason row is not allocated
		if (a)
			free(a[i]);
	}
	free(a);
}

void read_mat(int **a, int n, int m)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			scanf("%d", &a[i][j]);
}

void mult(int **a, int **b, int **temp, int n, int m, int nm)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			// Output matrix
			temp[i][j] = 0;
			// Common size
			for (int k = 0; k < nm; k++) {
				// MOD for overflow
				temp[i][j] += (a[i][k] % MOD) * (b[k][j] % MOD);
				temp[i][j] = temp[i][j] % MOD;

				if (temp[i][j] < 0)
					temp[i][j] += MOD;
			}
		}
	}
}

void print(int total, int ok, int ***v, int *n_m, int *m_m)
{
	int ind;
	scanf("%d", &ind);
	if (exist(total, ok, ind)) {
		for (int i = 0; i < n_m[ind]; i++) {
			for (int j = 0; j < m_m[ind]; j++)
				printf("%d ", v[ind][i][j]);
			printf("\n");
		}
	} else {
		printf("No matrix with the given index\n");
	}
}

void dim(int total, int ok, int *n_m, int *m_m)
{
	int ind;
	scanf("%d", &ind);
	if (exist(total, ok, ind))
		printf("%d %d\n", n_m[ind], m_m[ind]);
	else
		printf("No matrix with the given index\n");
}

void read_arr(int *vec, int n)
{
	for (int i = 0; i < n; i++)
		scanf("%d", &vec[i]);
}

void red_arr(int **n_mat, int **m_mat, int **sume, int n, int inc, int *leak)
{
	int *tmp;
	tmp = realloc(*n_mat, (n + inc + 1) * sizeof(int));
	if (!tmp)
		*leak = 1;
	else
		*n_mat = tmp;
	tmp = realloc(*m_mat, (n + inc + 1) * sizeof(int));
	if (!tmp)
		*leak = 1;
	else
		*m_mat = tmp;
	tmp = realloc(*sume, (n + inc + 1) * sizeof(int));
	if (!tmp)
		*leak = 1;
	else
		*sume = tmp;
}

void red_mat(int ****tab, int n, int inc, int *leak)
{
	int ***tmp;
	tmp = realloc(*tab, (n + inc + 1) * sizeof(int **));
	if (!tmp)
		*leak = 1;
	else
		*tab = tmp;
}

void add_mat(int n, int m, int ***v, int *n_m, int *m_m, int *i, int c, int *leak)
{
	int nr = *i;
	int **mat = alloc_mat(n, m);
	if (!mat) {
		*leak = 1;
	} else {
		// If adding matrix from keyboard
		if (c == 1)
			read_mat(mat, n, m);
		// Save size
		n_m[nr] = n;
		m_m[nr] = m;

		v[nr] = mat;
		// Id for next matrix
		(*i)++;
	}
}

int redim(int total, int ok, int ***v, int *n, int *m, int *leak)
{
	int ind;
	scanf("%d", &ind);
	// n, m for resizing
	int lin, col;
	scanf("%d", &lin);

	int *v_lin = malloc(lin * sizeof(int));
	if (!v_lin) {
		*leak = 1;
		return 0;
	}
	read_arr(v_lin, lin);

	scanf("%d", &col);
	int *v_col = malloc(col * sizeof(int));
	if (!v_col) {
		free(v_col);
		*leak = 1;
		return 0;
	}
	read_arr(v_col, col);
	if (!exist(total, ok, ind)) {
		free(v_lin);
		free(v_col);
		printf("No matrix with the given index\n");
	} else {
		// Output matrix
		int **temp = alloc_mat(lin, col);
		if (!temp) {
			free(v_lin);
			free(v_col);
			*leak = 1;
			return 0;
		}

		for (int i = 0; i < lin; i++) {
			for (int j = 0; j < col ; j++)
				temp[i][j] = v[ind][v_lin[i]][v_col[j]];
		}
		free_mat(v[ind], n[ind]);
		v[ind] = temp;
		free(v_lin);
		free(v_col);
		n[ind] = lin;
		m[ind] = col;
	}
	return 1;
}

int multip_verif(int total, int ok, int *n_m, int *m_m, int ind1, int ind2)
{
	if (!exist(total, ok, ind1) || !exist(total, ok, ind2)) {
		printf("No matrix with the given index\n");
		return 0;
	}

	if (m_m[ind1] != n_m[ind2]) {
		printf("Cannot perform matrix multiplication\n");
		return 0;
	}
	return 1;
}

void sum_all(int *sume, int ***v, int *n, int *m, int nr)
{
	for (int i = 0; i < nr; i++) {
		sume[i] = 0;
		for (int j = 0; j < n[i]; j++)
			for (int k = 0; k < m[i]; k++) {
				sume[i] += v[i][j][k] % MOD;
				sume[i] %= MOD;
				if (sume[i] < 0)
					sume[i] += MOD;
			}
	}
}

void swap_var(int *a, int *b)
{
	int aux = *a;
	*a = *b;
	*b = aux;
}

void sort_mat(int *sume, int ***v, int *n, int *m, int nr)
{
	for (int i = 0; i < nr - 1; i++) {
		for (int j = i + 1; j < nr; j++) {
			if (sume[i] > sume[j]) {
				swap_var(&sume[i], &sume[j]);
				int **aux = v[i];
				v[i] = v[j];
				v[j] = aux;
				swap_var(&n[i], &n[j]);
				swap_var(&m[i], &m[j]);
			}
		}
	}
}

void transp(int total, int ok, int ***v, int *n, int *m, int *leak)
{
	int ind;
	scanf("%d", &ind);
	if (!exist(total, ok, ind)) {
		printf("No matrix with the given index\n");
	} else {
		// Swap sizes
		int **temp = alloc_mat(m[ind], n[ind]);
		if (!temp) {
			*leak = 1;
		} else {
			for (int i = 0; i < n[ind]; i++) {
				for (int j = 0; j < m[ind]; j++)
					temp[j][i] = v[ind][i][j];
			}
				free_mat(v[ind], n[ind]);
				v[ind] = temp;
				swap_var(&n[ind], &m[ind]);
		}
	}
}

void copy_mat(int **a, int **b, int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			a[i][j] = b[i][j];
}

int pow_mat(int total, int ok, int ***v, int *n, int *m, int *leak)
{
	int ind, p;
	int verif = 1;
	scanf("%d %d", &ind, &p);
	if (!exist(total, ok, ind)) {
		printf("No matrix with the given index\n");
		verif = 0;
	}
	if (p < 0) {
		printf("Power should be positive\n");
		verif = 0;
	}
	if (verif) {
		if (n[ind] != m[ind]) {
			printf("Cannot perform matrix multiplication\n");
			verif = 0;
		}
	}
	// Verif is 1 as long as there are no errors
	if (verif == 1) {
		// Copy used for faster pows (when power is even)
		int **in = alloc_mat(n[ind], n[ind]);
		if (!in) {
			*leak = 1;
			return 0;
		}
		int **temp = alloc_mat(n[ind], n[ind]);
		if (!temp) {
			*leak = 1;
			free_mat(in, n[ind]);
			return 0;
		}
		// Identity matrix
		for (int i = 0; i < n[ind]; i++)
			for (int j = 0; j < n[ind]; j++) {
				if (i == j)
					in[i][i] = 1;
				else
					in[i][j] = 0;
		}
		while (p > 0) {
			// Odd power
			if (p % 2 == 1) {
				// Multiply once
				mult(v[ind], in, temp, n[ind], n[ind], n[ind]);
				copy_mat(in, temp, n[ind]);
			}
		// Then just square
		mult(v[ind], v[ind], temp, n[ind], n[ind], n[ind]);
		copy_mat(v[ind], temp, n[ind]);
		p /= 2;
		}

		copy_mat(v[ind], in, n[ind]);

		free_mat(in, n[ind]);
		free_mat(temp, n[ind]);
	}
	return 1;
}

void rem_mat(int total, int ind, int ***v, int *n, int *m)
{
	free_mat(v[ind], n[ind]);
	// Move all elements one position to the left
	for (int i = ind; i < total - 1; i++) {
		swap_var(&n[i], &n[i + 1]);
		swap_var(&m[i], &m[i + 1]);
		int **aux = v[i];
		v[i] = v[i + 1];
		v[i + 1] = aux;
	}
}

void clear_mem(int ***v, int *s, int *n, int *m, char *a, int nr)
{
	for (int i = 0; i < nr; i++) {
		if (v[i])
			free_mat(v[i], n[i]);
	}
		free(v);
		free(s);
		free(n);
		free(m);
		free(a);
}

int aloc_st(int ***v, int n, int n_m, int *leak)
{
	for (int i = 0; i < n; i++) {
		v[i] = alloc_mat(n_m, n_m);
		if (!v[i]) {
			for (int j = i; j > 0; j--)
				free_mat(v[j], n_m);
			*leak = 1;
			return 0;
		}
	}
	return 1;
}

void sum_mat(int **a, int **b, int **temp, int n)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			temp[i][j] = (a[i][j] % MOD + b[i][j] % MOD) % MOD;
			if (temp[i][j] < 0)
				temp[i][j] += MOD;
		}
	}
}

void dif_mat(int **a, int **b, int **temp, int n)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			temp[i][j] = (a[i][j] % MOD - b[i][j] % MOD) % MOD;
			if (temp[i][j] < 0)
				temp[i][j] += MOD;
		}
	}
}

void form_mini(int **t, int ***a, int n)
{
	for (int i = 0; i < n / 2; i++) {
		for (int j = 0; j < n / 2; j++) {
			a[0][i][j] = t[i][j];
			a[1][i][j] = t[i][j + n / 2];
			a[2][i][j] = t[i + n / 2][j];
			a[3][i][j] = t[i + n / 2][j + n / 2];
		}
	}
}

void q_mat(int ***c, int ***m, int n)
{
	//C1
	sum_mat(m[0], m[3], c[0], n);
	dif_mat(c[0], m[4], c[0], n);
	sum_mat(c[0], m[6], c[0], n);
	//C2
	sum_mat(m[2], m[4], c[1], n);
	//C3
	sum_mat(m[1], m[3], c[2], n);
	//C4
	dif_mat(m[0], m[1], c[3], n);
	sum_mat(c[3], m[2], c[3], n);
	sum_mat(c[3], m[5], c[3], n);
}

void strassen(int **t1, int **t2, int **temp, int n, int *leak)
{
	// 1 x 1 matrix
	if (n == 1) {
		temp[0][0] = ((t1[0][0] % MOD) * (t2[0][0] % MOD)) % MOD;
	if (temp[0][0] < 0)
		temp += MOD;
	} else {
		// Ai, Bi, Mi, Ci
		int ***a = malloc(4 * sizeof(int **));
		aloc_st(a, 4, n / 2, leak);
		int ***b = malloc(4 * sizeof(int **));
		aloc_st(b, 4, n / 2, leak);
		int ***m = malloc(7 * sizeof(int **));
		aloc_st(m, 7, n / 2, leak);
		// Accumulator for parenthesis
		int **left = alloc_mat(n / 2, n / 2);
		int **right = alloc_mat(n / 2, n / 2);
		int ***c = malloc(4 * sizeof(int **));
		aloc_st(c, 4, n / 2, leak);

		if (!*leak) {
			form_mini(t1, a, n);
			form_mini(t2, b, n);
			// M1..M7
			sum_mat(a[0], a[3], left, n / 2);
			sum_mat(b[0], b[3], right, n / 2);
			strassen(left, right, m[0], n / 2, leak);
			sum_mat(a[2], a[3], left, n / 2);
			strassen(left, b[0], m[1], n / 2, leak);
			dif_mat(b[1], b[3], right, n / 2);
			strassen(a[0], right, m[2], n / 2, leak);
			dif_mat(b[2], b[0], right, n / 2);
			strassen(a[3], right, m[3], n / 2, leak);
			sum_mat(a[0], a[1], left, n / 2);
			strassen(left, b[3], m[4], n / 2, leak);
			dif_mat(a[2], a[0], left, n / 2);
			sum_mat(b[0], b[1], right, n / 2);
			strassen(left, right, m[5], n / 2, leak);
			dif_mat(a[1], a[3], left, n / 2);
			sum_mat(b[2], b[3], right, n / 2);
			strassen(left, right, m[6], n / 2, leak);
			// C1..C4
			q_mat(c, m, n / 2);
			// n * n array created using recursive calls and the C's
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (i < n / 2 && j < n / 2)
						temp[i][j] = c[0][i][j];
					if (i < n / 2 && j >= n / 2)
						temp[i][j] = c[1][i][j - n / 2];
					if (i >= n / 2 && j < n / 2)
						temp[i][j] = c[2][i - n / 2][j];
					if (i >= n / 2 && j >= n / 2)
						temp[i][j] = c[3][i - n / 2][j - n / 2];
				}
			}
		}

		for (int i = 0; i < 4; i++) {
			if (a)
				free_mat(a[i], n / 2);
			if (b)
				free_mat(b[i], n / 2);
			if (c)
				free_mat(c[i], n / 2);
		}
		for (int i = 0; i < 7; i++)
			if (m)
				free_mat(m[i], n / 2);
		free(a);
		free(b);
		free(c);
		free(m);
		free_mat(left, n / 2);
		free_mat(right, n / 2);
	}
}
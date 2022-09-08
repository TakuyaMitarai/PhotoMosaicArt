#include "Individual.h"
#include <math.h>
#include <vector>
using namespace std;

extern vector<int> B, G, R;
extern vector<int> OB, OG, OR;

// �R���X�g���N�^
Individual::Individual()
{
	int i;

	for(i = 0; i < N; i++) {
		chrom[i] = rand() % MaterialPhotoNum;
	}
	fitness = 0.0;
}

// �f�X�g���N�^
Individual::~Individual()
{
}

// �K���x���Z�o����
void Individual::evaluate()
{
	int i;

	fitness = 0.0;
	for(i = 0; i < N; i++) {
		double dis = (B[chrom[i]] - OB[i]) * (B[chrom[i]] - OB[i]) + (G[chrom[i]] - OG[i]) * (G[chrom[i]] - OG[i]) + (R[chrom[i]] - OR[i]) * (R[chrom[i]] - OR[i]);
		dis = sqrt(dis);
		fitness += dis;
	}
	fitness = fabs(fitness);
}

// p1��p2�����_�����ō�����q�ɂ���
// p1: �e��1
// p2: �e��2
void Individual::crossover1(Individual *p1, Individual *p2)
{
	int point, i;

	point = rand() % (N - 1);
	for(i = 0; i <= point; i++) {
		chrom[i] = p1->chrom[i];
	}
	for(; i < N; i++) {
		chrom[i] = p2->chrom[i];
	}
}

// p1��p2�����_�����ō�����q�ɂ���
// p1: �e��1
// p2: �e��2
void Individual::crossover2(Individual *p1, Individual *p2)
{
	int point1, point2, tmp, i;

	point1 = rand() % (N - 1);
	point2 = (point1 + (rand() % (N - 2) + 1)) % (N - 1);
	if(point1 > point2) {
		tmp = point1;
		point1 = point2;
		point2 = tmp;
	}
	for(i = 0; i <= point1; i++) {
		chrom[i] = p1->chrom[i];
	}
	for(; i <= point2; i++) {
		chrom[i] = p2->chrom[i];
	}
	for(; i < N; i++) {
		chrom[i] = p1->chrom[i];
	}
}

// p1��p2�����l�����ō�����q�ɂ���
// p1: �e��1
// p2: �e��2
void Individual::crossoveru(Individual *p1, Individual *p2)
{
	int i;

	for(i = 0; i < N; i++) {
		if(rand() % 2 == 1) {
			chrom[i] = p1->chrom[i];
		} else {
			chrom[i] = p2->chrom[i];
		}
	}
}

// �ˑR�ψق��N����
void Individual::mutate()
{
	int i;

	for(i = 0; i < N; i++) {
		if(RAND_01 < MUTATE_PROB) {
			chrom[i] = rand() % MaterialPhotoNum;
		}
	}
}

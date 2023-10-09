#include <stdio.h>
#include <stdlib.h>

// 定义稀疏数组结构
typedef struct {
    int row;
    int col;
    int val;
} SparseArray;

int main() {
    const int ROW = 5;
    const int COL = 5;
    int chess[ROW][COL];
    int sum = 0;

    // 初始化棋盘
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            chess[i][j] = 0;
        }
    }

    // 添加非零元素
    chess[1][2] = 1;
    chess[2][3] = 1;

    // 打印棋盘
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            printf("%5d", chess[i][j]);
            if (chess[i][j] != 0) {
                sum++;
            }
        }
        printf("\n");
    }

    // 创建稀疏数组
    SparseArray *sparseArr = (SparseArray *)malloc(sizeof(SparseArray) * (sum + 1));
    sparseArr[0].row = ROW;
    sparseArr[0].col = COL;
    sparseArr[0].val = sum;

    int index = 1;
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            if (chess[i][j] != 0) {
                sparseArr[index].row = i;
                sparseArr[index].col = j;
                sparseArr[index].val = chess[i][j];
                index++;
            }
        }
    }

    // 将稀疏数组写入文件
    FILE *file = fopen("sparse_array.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    for (int i = 0; i <= sum; i++) {
        fprintf(file, "%d %d %d\n", sparseArr[i].row, sparseArr[i].col, sparseArr[i].val);
    }

    fclose(file);

    // 从文件中读取稀疏数组
    file = fopen("sparse_array.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int numRows, numCols, numVals;
    fscanf(file, "%d %d %d", &numRows, &numCols, &numVals);
    SparseArray *readSparseArr = (SparseArray *)malloc(sizeof(SparseArray) * (numVals + 1));
    readSparseArr[0].row = numRows;
    readSparseArr[0].col = numCols;
    readSparseArr[0].val = numVals;

    for (int i = 1; i <= numVals; i++) {
        fscanf(file, "%d %d %d", &readSparseArr[i].row, &readSparseArr[i].col, &readSparseArr[i].val);
    }

    fclose(file);

    // 打印从文件中读取的稀疏数组
    printf("Sparse Array from File:\n");
    for (int i = 0; i <= numVals; i++) {
        printf("%d %d %d\n", readSparseArr[i].row, readSparseArr[i].col, readSparseArr[i].val);
    }

    free(sparseArr);
    free(readSparseArr);

    return 0;
}

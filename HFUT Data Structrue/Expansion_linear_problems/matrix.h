#define maxnum 10
using namespace std;

#include <iostream>
#include <vector>

struct Tuple {
    int i, j; //Ԫ�ص������±�
    int value; //Ԫ�ص�ֵ
};

typedef struct
{
    int mu, nu, tu; //Ԫ�ص�����������������Ԫ�ظ���
    Tuple data[maxnum];
} spmatrix;

vector<spmatrix> reset()
{
    int num;
    cout << "��Ҫ�������ٸ�����" << endl;
    cin >> num;
    vector<spmatrix> s;
    s.resize(num);
    cout << "��Ҫ������������������ֱ�Ϊ���٣�" << endl;
    int mu, nu;
    cin >> mu >> nu;
    for (int i = 0; i < num; ++i) {
        s[i].mu = mu;
        s[i].nu = nu;
    }
    for (int i = 0; i < num; ++i) {
        cout << "��" << i + 1 << "������ķ���Ԫ�ظ�����";
        int num_of_nzero;
        cin >> num_of_nzero;
        s[i].tu = num_of_nzero;
    }
    return s;
}

void insert(vector<spmatrix>& s)
{
    int num = s.size();
    for (int m = 0; m < num; ++m) {
        int num_of_nzero = s[m].tu;
        for (int n = 0; n < num_of_nzero; ++n) {
            int i, j, value;
            cout << "�㴴���ĵ�" << m + 1 << "���������Ԫ�ص����к�Ԫ��ֵ�ֱ�Ϊ��";
            cin >> i >> j >> value;
            s[m].data[n].i = i; //��n������Ԫ�ص��б�
            s[m].data[n].j = j; //��n������Ԫ�ص��б�
            s[m].data[n].value = value;
        }
    }
}

void pirnt_matrix(vector<vector<int>> v)
{
    for (int i = 0; i < v.size(); ++i) {
        int count = 0;
        for (auto c : v[i]) {
            cout << c << ' ';
            count++;
            if (count == v[0].size()) {
                cout << endl;
                count = 0;
            }
        }
    }
}

void copy_value(const vector<spmatrix>& s, vector<vector<int>> v)
{
    for (int j = 0; j < s[0].tu; ++j) {
        //��j������Ԫ�� �бꡢ�бꡢԪ��ֵ
        int I = s[0].data[j].i, J = s[0].data[j].j, V = s[0].data[j].value;
        v[I - 1][J - 1] = V; //������бꡢ�б���ϰ���ϵĴ�1��ʼ
    }
}

void plus_spmatrix(const vector<spmatrix>& s)
{
    vector<vector<int>> v;
    v.resize(s[0].mu);

    for (int i = 0; i < v.size(); ++i) {
        v[i].resize(s[0].nu);
    }

    int n = 1;
    //��δ���Ƿ���Ԫ��Ϊ0�����
    for (int j = 0; j < s[0].tu; ++j) {
        //��j������Ԫ�� �бꡢ�бꡢԪ��ֵ
        int I = s[0].data[j].i, J = s[0].data[j].j, V = s[0].data[j].value;
        v[I - 1][J - 1] = V; //������бꡢ�б���ϰ���ϵĴ�1��ʼ
    }

    //��ӡ����
    //pirnt_matrix(v);

    //��һ��ϡ������Ѿ���ֵ���ӵڶ�����ʼ��
    while (n != s.size()) {
        for (int j = 0; j < s[n].tu; ++j) {
            int I = s[n].data[j].i, J = s[n].data[j].j, V = s[n].data[j].value;
            v[I - 1][J - 1] += V;
        }
        n++;
    }
    pirnt_matrix(v);
}

void multiply_spmatrix(const vector<spmatrix>& s)
{
    int n = 1;
    vector<vector<int>> v;
    v.resize(s[0].mu);

    for (int i = 0; i < v.size(); ++i) {
        v[i].resize(s[0].nu);
    }
    //����һ��ϡ�����copy����άvector��
    for (int j = 0; j < s[0].tu; ++j) {
        //��j������Ԫ�� �бꡢ�бꡢԪ��ֵ
        int I = s[0].data[j].i, J = s[0].data[j].j, V = s[0].data[j].value;
        v[I - 1][J - 1] = V; //������бꡢ�б���ϰ���ϵĴ�1��ʼ
    }
    pirnt_matrix(v);

    //�ٿ���һ�������Ž��
    vector<vector<int>> v2;
    v2.resize(s[n].mu);

    for (int i = 0; i < v2.size(); ++i) {
        v2[i].resize(s[n].nu);
    }

    while (n != s.size()) {
        //ÿ����ѭ���ڴ���һ��vector������¼�˷��к�һ��ϡ�����
        vector<vector<int>> v1;
        v1.resize(s[n].mu);

        for (int i = 0; i < v1.size(); ++i) {
            v1[i].resize(s[n].nu);
        }

        for (int j = 0; j < s[n].tu; ++j) {
            //��j������Ԫ�� �бꡢ�бꡢԪ��ֵ
            int I = s[n].data[j].i, J = s[n].data[j].j, V = s[n].data[j].value;
            v1[I - 1][J - 1] = V; //������бꡢ�б���ϰ���ϵĴ�1��ʼ
        }

        for (int i = 0; i < v.size(); ++i) {
            for (int j = 0; j < v1[i].size(); ++j) {
                int sum = 0;
                for (int k = 0; k < v[i].size(); ++k) {
                    sum += v[i][k] * v1[k][j];
                }
                v2[i][j] = sum;
            }
        }
        //һ�ֳ˷���ϣ��ٽ�v2��ŵĳ˷������ֵ��v��ʵ��n�����
        v.swap(v2);
        ++n;//������һ�ֳ˷�
    }
    pirnt_matrix(v);
}

#include <fstream>
#include <iostream>
#include<string>
#include <queue> //��������
using namespace std;
const int leaf = 256; //�����ܳ��ֵĲ�ͬ�ַ���

//huffman���Ľ��ṹ��
class HTnode {
public:
    long weight; //��¼����Ȩֵ
    int parent; //��¼����˫�׽��λ��
    int lchild; //��������
    int rchild; //�����Һ���
    int* code; //��¼�ý���huffman����
    int codelen; //��¼�ý��huffman����ĳ���

    //��ʼ����㣬����ȨֵΪ�������˫�׼����Һ���
    HTnode():weight(INT_MAX),parent(-1),lchild(-1),rchild(-1),codelen(0){}
};
//huffman����
class huffmanTree {
public:
    huffmanTree():root(0),leafnum(0),byte(0),bitsnum(0),lacknum(0){}
    virtual ~huffmanTree();
    bool count(string input); //ѹ��ʱͳ�Ƹ��ַ����ֵĴ���������д���Ӧ����Ȩֵ
    void create(); //ѹ��ʱ���ݸ�����Ȩֵ����huffman��
    void code(); //ѹ��ʱ�����ý��õ�huffman������ÿ���ַ���huffman����
    void printcode(); //�г�ÿ���ַ���huffman����
    void addbit(int bit); //ѹ��ʱ��һ��δ��8��bit��byte�м���һ��bit
    void resetbyte(); //��byte���
    bool compress(string input, string output); //ѹ������ �ɹ�ִ�з��� true ʧ�� false
    bool decompress(string input, string output); //�ָ����� �ɹ�ִ�з��� true ʧ�� false
    void compare(string input, string output); //��ԭ�ļ���ѹ������ļ��Ƚ�
    void compare2(string input, string output); //��ԭ�ļ���ָ�����ļ��Ƚ�


private:
    int root; //��¼������λ��
    int leafnum; //��¼��ͬ�ַ��ĸ���
    HTnode HT[leaf * 2 - 1]; //HTnode�ṹ�����飬������ʾhuffman�������������������ᳬ��leaf*2-1
    char byte; //ѹ���ļ�ʱ��������bit�ı���
    int bitsnum; //byte��bit�ĸ���
    int lacknum; //ѹ�������byte�е�bit����8��ʱ����0�ĸ���
};

huffmanTree::~huffmanTree()
{
    for (int i = 0; i < leaf; i++) {
        if (HT[i].codelen != 0)
            delete HT[i].code;
    }
}

//ͳ�Ƹ��ַ����ֵĴ���
bool huffmanTree::count(string input)
{
    ifstream ifs;
    char c;
    ifs.open(input, ios::binary);
    if (!ifs) {
        cout << "�޷����ļ� " << input << '!' << endl;
        return false;
    }
    while (ifs.get(c)) {
        if (HT[c + 128].weight == INT_MAX) { //�����ַ��ǵ�һ�γ��֣��ȳ�ʼ��Ȩֵ
            HT[c + 128].weight = 0;
            leafnum++;
        }
        HT[c + 128].weight++; //Ȩֵ+1
    }
    ifs.close();
    return true;
}

//ѡȨֵ��С������������µ���
void huffmanTree::create()
{
    for (int i = leaf; i < 2 * leaf - 1; i++) {
        int loc1 = -1, loc2 = -1;
        for (int j = 0; j < i; j++) {
            if (HT[j].parent != -1)
                continue;
            if (loc1 == -1 || HT[j].weight < HT[loc1].weight) {
                loc2 = loc1;
                loc1 = j;
            } else if (loc2 == -1 || HT[j].weight < HT[loc2].weight)
                loc2 = j;
        }
        if (HT[loc1].weight == INT_MAX || HT[loc2].weight == INT_MAX || loc2 == -1) //ֻʣһ����������
            break;
        HT[i].weight = HT[loc1].weight + HT[loc2].weight;
        //Ϊ�˼���ѹ���ļ�����Ҫд���huffman������Ϣ��Լ��С��С�Ľ����Ϊ˫�׽�������
        HT[i].lchild = (loc1 > loc2) ? loc2 : loc1;
        HT[i].rchild = (loc1 > loc2) ? loc1 : loc2;
        HT[loc1].parent = i;
        HT[loc2].parent = i;
        root = i;
    }
}

//ѹ��ʱ�����ý��õ�huffman������ÿ���ַ���huffman����
void huffmanTree::code()
{
    for (int i = 0; i < leaf; i++) {
        int len = 0;
        int loc = i;
        while (HT[loc].parent != -1) { //����huffman���볤��
            len++;
            loc = HT[loc].parent;
        }
        HT[i].codelen = len;
        HT[i].code = new int[len];
        loc = i;
        for (int j = len - 1; j >= 0; j--) { //�Ӻ���ǰ�ң���¼����huffman����
            if (loc == HT[HT[loc].parent].lchild)
                HT[i].code[j] = 0;
            else
                HT[i].code[j] = 1;
            loc = HT[loc].parent;
        }
    }
}

//ѹ��ʱ��һ��δ��8��bit��byte�м���һ��bit
void huffmanTree::addbit(int bit)
{
    if (bit == 0)
        byte = byte << 1; //��������bitΪ0����ֱ�ӽ�byte��λ����
    else
        byte = ((byte << 1) | 1); //��������bitΪ1���Ƚ�byte��λ���ƣ�����1��λ������
    bitsnum++;
}

//��byte���
void huffmanTree::resetbyte()
{
    byte = 0;
    bitsnum = 0;
}

//�г�ÿ���ַ���huffman����
void huffmanTree::printcode()
{
    for (int i = 0; i < leaf; i++) {
        if (HT[i].codelen != 0) {
            cout << "ֵΪ" << i - 128 << "���ַ���huffman���룺";
            for (int j = 0; j < HT[i].codelen; j++) {
                cout << HT[i].code[j];
            }
            cout << endl;
        }
    }
}

//ѹ������ �ɹ�ִ�з��� true ʧ�� false
bool huffmanTree::compress(string input, string output)
{
    if (!count(input))
        return false;

    create();
    code();
    ifstream ifs;
    ofstream ofs;
    ifs.open(input, ios::binary);
    ofs.open(output, ios::binary);
    char c;
    if (!ifs) {
        cout << "�޷����ļ� " << input << '!' << endl;
        return false;
    }
    if (!ofs) {
        cout << "�޷����ļ� " << output << '!' << endl;
        return false;
    }

    ofs.put(0); //Ԥ��һ���ַ�����ѹ������ڸ�λ��д�벻��һ��byte��bit����
    ofs.put(root - 384); //�����ڵ��λ��-384д�루Ϊʹ��ֵ������char������ʾ��Χ��
    for (int i = 0; i < leaf * 2 - 1; i++) { //д��ÿ������˫�׽��λ��
        if (HT[i].parent == -1) //���ýڵ�û��˫�׽�㣬��д��127(һ���ֽ����ܱ�ʾ�����ֵ)
            ofs.put(127);
        else //����˫�׽���λ��-384��д�루Ϊʹ��ֵ������char������ʾ��Χ��
            ofs.put(HT[i].parent - 384);
    }

    while (ifs.get(c)) { //���ַ���huffman���벢����byte��
        int tmp = c + 128;
        for (int i = 0; i < HT[tmp].codelen; i++) {
            addbit(HT[tmp].code[i]);
            if (bitsnum == 8) { //��byte����8λ���������byte����byte���
                ofs.put(byte);
                resetbyte();
            }
        }
    }
    if (bitsnum != 0) { //�������δ��8���ַ���byte����0��䲢��¼���ĸ���
        for (int i = bitsnum; i < 8; i++) {
            addbit(0);
            lacknum++;
        }
        ofs.put(byte);
        resetbyte();
    }
    ofs.seekp(0, ios::beg); //��дָ���ƶ����ļ���ͷ
    ofs.put(lacknum); //д�����һ���ֽ�ȱʧ��bit����
    ifs.close();
    ofs.close();
    return true;
}

//�ָ����� �ɹ�ִ�з��� true ʧ�� false
bool huffmanTree::decompress(string input, string output)
{
    queue<char> q;
    char c;
    ifstream ifs;
    ofstream ofs;
    ifs.open(input, ios::binary);
    ofs.open(output, ios::binary);
    if (!ifs) {
        cout << "�޷����ļ� " << input << '!' << endl;
        return true;
    }
    if (!ofs) {
        cout << "�޷����ļ� " << output << '!' << endl;
        return false;
    }

    ifs.get(c);
    lacknum = c; //�������һ���ֽ�ȱʧ��bit����
    ifs.get(c);
    root = c + 384; //����������λ��
    for (int i = 0; i < leaf * 2 - 1; i++) { //���������֮���˫�׺��ӹ�ϵ
        ifs.get(c);
        if (c == 127)
            continue;
        else {
            HT[i].parent = c + 384;
            if (HT[c + 384].lchild == -1)
                HT[c + 384].lchild = i;
            else
                HT[c + 384].rchild = i;
        }
    }

    int point = root;
    //Ϊ�˷��㴦�����һ��������ȱʧbit���ֽڣ��Ƚ����������ݷ������
    while (ifs.get(c))
        q.push(c);

    //��ԭ�ļ�����
    while (q.size() > 1) { //��δ�����һ���ֽ�
        c = q.front();
        for (int i = 0; i < 8; i++) {
            if (int(c & 128) == 0) {
                point = HT[point].lchild;
                if (HT[point].lchild == -1 && HT[point].rchild == -1) {
                    ofs.put(char(point - 128));
                    point = root;
                }
                c = c << 1;
            } else {
                point = HT[point].rchild;
                if (HT[point].lchild == -1 && HT[point].rchild == -1) {
                    ofs.put(char(point - 128));
                    point = root;
                }
                c = c << 1;
            }
        }
        q.pop();
    }
    c = q.front(); //���һ���ֽ�
    for (int i = 0; i < 8 - lacknum; i++) {
        if (int(c & 128) == 0) {
            point = HT[point].lchild;
            if (HT[point].lchild == -1 && HT[point].rchild == -1) {
                ofs.put(char(point - 128));
                point = root;
            }
            c = c << 1;
        } else {
            point = HT[point].rchild;
            if (HT[point].lchild == -1 && HT[point].rchild == -1) {
                ofs.put(char(point - 128));
                point = root;
            }
            c = c << 1;
        }
    }
    q.pop();
    ifs.close();
    ofs.close();
    return true;
}

//��ԭ�ļ���ѹ������ļ��Ƚ�
void huffmanTree::compare(string input, string output)
{
    ifstream origin, compress;
    origin.open(input, ios::binary);
    compress.open(output, ios::binary);

    if (!origin) {
        cout << "�޷����ļ� " << input << '!' << endl;
        return;
    }
    if (!compress) {
        cout << "�޷����ļ� " << output << '!' << endl;
        return;
    }
    double total1 = 0, total2 = 0;
    char c;
    while (origin.get(c))
        total1++;
    while (compress.get(c))
        total2++;
    cout << "ԭ�ļ���С��" << total1 << " Byte" << endl;
    cout << "ѹ�����С��" << total2 << " Byte" << endl;
    cout << "ѹ���ʣ�" << total2 / total1 * 100 << '%' << endl;
    origin.close();
    compress.close();
}

//��ԭ�ļ���ָ�����ļ��Ƚ�
void huffmanTree::compare2(string input, string output)
{
    ifstream origin, decompress;
    origin.open(input, ios::binary);
    decompress.open(output, ios::binary);
    double total1 = 0, total2 = 0;
    char c1, c2;
    bool dif = false;
    while (origin.get(c1) && decompress.get(c2)) {
        if (c1 != c2) //���αȽ�ÿ���ֽڣ���ͬ��dif��־��Ϊtrue
            dif = true;
        total1++;
        total2++;
    }
    while (origin.get(c1)) { //��ԭ�ļ�����ʣ������ݣ���dif��Ϊtrue
        dif = true;
        total1++;
    }
    while (decompress.get(c2)) { //���ָ��ļ�����ʣ������ݣ���dif��Ϊtrue
        dif = true;
        total2++;
    }
    cout << "ԭ�ļ���С��" << total1 << " Byte" << endl;
    cout << "�ָ��ļ���С��" << total2 << " Byte" << endl;
    if (dif == true)
        cout << "ԭ�ļ���ָ��ļ���ͬ!" << endl;
    else
        cout << "ԭ�ļ���ָ��ļ���ͬ!" << endl;
    origin.close();
    decompress.close();
}


int main()
{
    int choice;
    char input[255], output[255];
    huffmanTree h;
    while (true) {
        cout << "	***************************************************" << endl;
        cout << "	*               ����������ѹ���ָ��㷨             *" << endl;
        cout << "	*                                                  *" << endl;
        cout << "	*                    1)ѹ��                        *" << endl;
        cout << "	*                                                  *" << endl;
        cout << "	*                    2) �ָ�                       *" << endl;
        cout << "	*                                                  *" << endl;
        cout << "	*                    3) �ָ��ļ���ԭ�ļ��ĶԱ�     *" << endl;
        cout << "	*                                                  *" << endl;
        cout << "	*                    4) ����                       *" << endl;
        cout << "	*                                                  *" << endl;
        cout << "	*                    5) �˳�                       *" << endl;
        cout << "	*                                                  *" << endl;
        cout << "	*        ˵��������������Ӧ�Ĳ�����Ž��в���      *" << endl;
        cout << "	****************************************************" << endl;
        cout << ">";
        cin >> choice;
        switch (choice) {
        case 1: {
            cout << "�������ѹ�����ļ�����";
            cin >> input;
            cout << "������ѹ������ļ�����";
            cin >> output;
            if (h.compress(input, output)) {
                h.printcode();
                h.compare(input, output);
                cout << endl
                     << "�ļ�ѹ���ɹ�!" << endl;
            } else {
                cout << endl
                     << "�ļ�ѹ��ʧ��!" << endl;
            }
        } break;
        case 2: {
            cout << "��������ָ����ļ�����";
            cin >> input;
            cout << "������ָ�����ļ�����";
            cin >> output;
            if (h.decompress(input, output))
                cout << endl
                     << "�ļ��ָ��ɹ�!" << endl;
            else
                cout << endl
                     << "�ļ��ָ�ʧ��!" << endl;
        } break;
        case 3: {
            cout << "������ԭ�ļ����ļ�����";
            cin >> input;
            cout << "������ָ��ļ����ļ�����";
            cin >> output;
            h.compare2(input, output);
        } break;
        case 4: {
            //ִ����������
            system("cls");
        } break;
        case 5:
            exit(0);
        }
        cout << endl;
    }
    return 0;
}
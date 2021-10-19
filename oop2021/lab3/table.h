#ifndef TABLE_H
#define TABLE_H

using namespace std;

typedef struct Item {
	int key;
	int release;
	char* info;
}; Item

class Tables {
    private:
        int n;  //������� ������ �������
        struct Item item[]; //������ ��������� �������
    public:
        int find_by_key(int key) const; //����� �������� ������� �� �����
        void add(int key, char* str); //���������� �������� � ������� //����������� //const
        void delete_by_key(int key); //�������� �������� �� ������� �� ����� //�����������
        void modify(int key, char* str); //����������� ���������� � ������ � �������� ������
        void get_by_index(int i, char* str, unsigned int length) const;  //��������� ���������� �� ������� � �������
        void find_and_show() const; //����� �������� � ����� ���������� � �������� �����
};

bool correct_get_int(int& a) noexcept;
int get_int() noexcept;
#endif //table_h
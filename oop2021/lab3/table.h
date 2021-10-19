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
        int n;  //текущий размер таблицы
        struct Item item[]; //массив элементов таблицы
    public:
        int find_by_key(int key) const; //поиск элемента таблицы по ключу
        void add(int key, char* str); //добавление элемента в таблицу //перегрузить //const
        void delete_by_key(int key); //удаление элемента из таблицы по ключу //перегрузить
        void modify(int key, char* str); //модификация информации в записи с заданным ключом
        void get_by_index(int i, char* str, unsigned int length) const;  //получение информации по индексу в таблице
        void find_and_show() const; //поиск элемента и вывод информации в выходной поток
};

bool correct_get_int(int& a) noexcept;
int get_int() noexcept;
#endif //table_h
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
struct film
{
    std::string name;//название 
    std::string director;//режиссер
    std::string country;//страна 
    int year;//год выпуска
    int price;//стоимость 
    int income;//доход
};
int read(film *&f, std::ifstream &file)//функция которая будет читать с файла
{
    int size = (std::count(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), '\n')+1) / 6; // делим на 6 так как у нас 6 полей 
    file.seekg(0);
    f = new film[size];
    for(int i = 0;i<size;++i)//проходим по всему файлу 
    {
    std::string temp;
    std::getline(file, f[i].name);
    std::getline(file, f[i].director);
    std::getline(file, f[i].country);
    std::getline(file, temp);
    f[i].year = stoi(temp);//используем для чисел
    std::getline(file, temp);
    f[i].price = stoi(temp);
    std::getline(file, temp);
    f[i].income = stoi(temp);
    }
    return size;
}
void delete_struct(film*&f, int elem, int& size)
{
    if(size == 0) return ;
    if(size == 1)
    {
        delete[]f;
        f = new film[0];
        size = 0;
        return;
    }
    film * temp = new film[size -1];
    for(int i = 0;i<elem;i++) temp[i] = f[i];
    for(int i = elem + 1; i < size; i++) temp[i - 1] = f[i];
    delete[] f;
    f = temp;
    size--;
}
void write(const film &f, std::fstream &file)//функция которая будет записывать в файл
{
    file << f.name << "\n";
    file << f.director << "\n";
    file << f.country << "\n";
    file << f.year << "\n";
    file << f.price << "\n";
    file << f.income << "\n";
}
void search_by_name(film * arr, std::string name, int size)
{
    for(int i=0;i<size;i++)
    {
        if(arr[i].name == name)
         {
            std::cout << arr[i].name << "\n";
            std::cout << arr[i].director << "\n";
            std::cout << arr[i].country << "\n";
            std::cout << arr[i].year << "\n";
            std::cout << arr[i].price << "\n";
            std::cout << arr[i].income << "\n";
           }
      }
}
int main()
{
    std::fstream file;
    file.open("C:/coding/laba 5.2/data1.txt", std::ios_base::app | std::ios_base::in);//открываем файл
    std::string path = "C:/coding/laba 5.2/data1.txt";
    film movie1;
    movie1.director = "Refn";
    movie1.name = "drive";
    movie1.country = "USA";
    movie1.year = 2011;
    movie1.price = 15000000;
    movie1.income = 82000000;
    write(movie1, file);//записываем в файл
    file.close();//закрываем файл
    std::ifstream file2;
    std::fstream output;

    file2.open(path);//открываем файл
    film* movie;
    int size = read(movie,file2);
    file2.close();
    output.open(path,std::ios::out | std::ios::in);
    std::cout << "Исходный файл\n";
    
    for(int i =0; i < size; ++i){std::cout << movie[i].name << " " << movie[i].director << " " << movie[i].country << "  " << movie[i].year  << " " << movie[i].price << " " << movie[i].income << "\n"; write(movie[i], output);}
    output.close();
    delete_struct(movie, 2, size);// структуру которую нужно удалить
    output.open(path,  std::ios::out | std::ios::trunc);
    std::cout << "Файл после удаления" << "\n";
    for(int i =0; i < size; ++i)
    {
        std::cout << movie[i].name << " " << movie[i].director << " " << movie[i].country << "  " << movie[i].year  << " " << movie[i].price << " " << movie[i].income << "\n"; 
        write(movie[i], output);
    }
    std::cout << "Поиск по имени\n";// поле которое нужно найти 
    search_by_name(movie,"spring",size);
}
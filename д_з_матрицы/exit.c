
#include <stdio.h>   //Для puts
#include <stdlib.h>  //Для exit () и atexit ()

void f_MyEnd (void); //Декларация функций, которая будет вызвана при
                     //завершении работы с помощью функции exit ()

int main (void)
{   
   int Pwork=0;
   int MyChar=0;
    
   //Регистрация функции, которая будет вызвана при
   //нормальном завершении работы
   Pwork = atexit (f_MyEnd);
   //Проверка регистрации функции MyEnd_s
   if (Pwork != 0)  
   {   
      puts ("Ошибка регистрации функции f_MyEnd ");
   }
   //Бесконечный цикл
   while (1)
   {  
      //Считывание символа из стандартного потока ввода-вывода
      MyChar = getchar ();
      //Если считан симовл ‘e’ завершаем работу программы
      if (MyChar == 'e')
         exit (EXIT_SUCCESS); //Завершение работы программы
   }

   return 0; 
} 


//Функция, вызываемая при завершении работы
void f_MyEnd (void)
{   
   //Вывод сообщения о завершении работы
   puts ("Работа завершена");
}
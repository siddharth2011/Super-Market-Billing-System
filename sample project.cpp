#include<iostream>
#include<windows.h>
#include<fstream>
#include<conio.h>
using namespace std;




// =============================== creating class product =============================================//

class product
{
    int pno;
    float dis,price;
    char name[50];
public:
    int create_prod()
    {
        cout<<"\n\tPlease enter the Product.No of the Product: ";
        cin>>pno;
        cout<<"\n\tEnter the Name of the Product: ";
        cin>>name;
        cout<<"\n\tPlease Enter the price of the product: ";
        cin>>price;
        cout<<"\n\tPlease Enter the discount(%) of the Product: ";
        cin>>dis;
    }
    int show_prod()
    {
        cout<<"Product.No of the Product: "<<pno;
        cout<<"\nName of gthe Product: "<<name;
        cout<<"\nPrice of the Product: "<<price;
        cout<<"\nDiscount (%) on that product: "<<dis;
    }

    int Pno()
    {
        return pno;
    }
    char* Name()
    {
        return name;
    }
    float Price()
    {
        return price;
    }
    float Dis()
    {
        return dis;
    }

};



fstream Mymenu;  // global declaration of stream
product pr; // global declaration of class object






// ============================================= Function to move cursor =========================================//
int gotoxy(int x,int y)
{
    COORD coord;
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
    return 0;
}






//  ================================================  Intro  ================================================//

int intro()
{

    gotoxy(45,5);
    cout<<"Supermarket Billing System";
    return 0;
}







//====================================  Menu  ============================================//
int menu()
{
    Mymenu.read("sid.dat",ios::out);
    if(!Mymenu)
    {
        cout<<"Error! file not found";
        cout<<"\n\nGo to the Admin menu to create a new file";
        cout<<"\n\nProgram Closing\n\n";

        exit(10);
    }
    cout<<"Menu for Super Market";
    cout<<"============================";
    cout<<"P.No\t\tName\t\tPrice";
    cout<<"============================";
    while(Mymenu.read((char*)&pr,sizeof(product)))
    {
        cout<<pr.Pno()<<"\t\t"<<pr.Name()<<"\t\t"<<pr.Price();
    }
    Mymenu.close();

}








//=========================================Modify Prod ==============================================//
int modify_prod()
{
    int no,found=0;
    cout<<"Modify Your Product";
    cout<<"\n\n\tPlease Enter The Product No. of The Product";
    cin>>no;
    Mymenu.open("sid.dat",ios::in | ios::out);
    while(Mymenu.read((char*)&pr,sizeof(product)&&found==0))
          {
              if(no==pr.Pno())
            {
                pr.show_prod();
                cout<<"\nPlease Enter the dtails";
                int pos=-1*sizeof(pr);
                Mymenu.seekp(pos,ios::cur);
                Mymenu.write((char*)&pr,sizeof(product));
                cout<<"\n\n\t Record Updated";
                found=1;
            }
          }
          Mymenu.close();
          if(found==0)
            cout<<"\nRecord Not found";
}





//========================================= Function to place the order =============================//

int place_order()
{
    int pno[50],quant[50],c=0;
    float total=0,amt,damt;
    char ch='y';
    menu();
    cout<<"============================";
    cout<<"     Place Your Order";
    cout<<"============================";

    cout<<"\n\n\n";
    do{
            cout<<"Enter the Product.No of the Product: ";
            cin>>pno[c];
            cout<<"Enter Quantity: ";
            cin>>quant[c];
            c++;
            cout<<"Do you want to add more items?(y/n): ";
            cin>>ch;

    }while(ch=='y' || ch=='Y');
    cout<<"Thank You for Placing order";
    cout<<"************************INVOICE************************";
    cout<<"================================================================";
    cout<<"P.no\tPr.Name\tQuantity\tPrice\tAmount\tAmount After Discount";
    cout<<"================================================================";
    for(int x=0;x<=c;x++)
    {
        Mymenu.open("sid.dat",ios::in);
        Mymenu.read((char*)&pr,sizeof(product));
        while(!Mymenu.eof())
            {
                if(pno[x]==pr.Pno())
                {
                    amt=pr.Price()*quant[x];
                    damt=amt-(amt*pr.Dis()/100);
                    cout<<"\n"<<pno[x]<<"\t"<<pr.Name()<<"\t"<<quant[x]<<"\t"<<pr.Price()<<"\t"<<amt<<"\t"<<"damt";

                    total+=damt;
                }
                Mymenu.read((char*)&pr,sizeof(product));
            }
            Mymenu.close();
    }
    cout<<"\t\t\t\t\t\tTotal: "<<total;

}







//===================================== write_prod function ===============================================//
int write_prod()
{
    system("CLS");
        cout<<flush;
    Mymenu.open("sid.dat",ios::in | ios::out);
    pr.create_prod();
    Mymenu.write((char*)&pr,sizeof(product));
    Mymenu.close();
    cout<<"\n\tProduct Created";
}





//========================================= Function for administrator Menu =======================================
int admin_menu()
{
    cout<<"\n\n\n\t\t\t\t\t\t    Admin Menu";
    cout<<"\n\n\t\t\t\t\t1. Create Product";
    cout<<"\n\n\t\t\t\t\t2. Display Product Menu";
    cout<<"\n\n\t\t\t\t\t3. Modify Product";
    cout<<"\n\n\t\t\t\t\t4. Main Menu";
    char ch2;
    cout<<"\n\n\t\t\t\t\t Enter your Option: ";
    ch2=getche();
    switch(ch2)
    {
    case '1':
        system("CLS");
        cout<<flush;
        write_prod();
        break;
    case '2':
        system("CLS");
        cout<<flush;
        menu();
        break;
    case '3':
        system("CLS");
        cout<<flush;
        modify_prod();
        break;
    case '4':
        system("CLS");
        cout<<flush;
        break;
    default:cout<<"\a";admin_menu();
    }
}




// ========================================================  MAIN  ================================================//
int main()
{
    char ch;
    intro();

    do{

       cout<<"\n\n\n\tMain Menu";

        cout<<"\n\n\t1. Customer";

        cout<<"\n\n\t2. Administrator";

        cout<<"\n\n\t3. Exit";

        cout<<"\n\n\tSelect your option(1-3): ";

        ch=getche();
        switch(ch)
        {
            case '1':
                system("CLS");
                cout<<flush;
                place_order();
                break;
            case '2':
                system("CLS");
                cout<<flush;
                admin_menu();
                break;
            case '3':
                exit(0);
        }
    }while(ch>= '1' || ch<='3');

}



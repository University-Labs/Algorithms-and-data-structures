#include "stdafx.h"
#include <fstream>
#include <iostream>

using namespace std;

class list{
public:
	list(){
		head = nullptr;
	}
	~list(){
		clear();
	}

	void push_back(int data);//Çàïèñü â êîíåö
	void push_front(int data);//Äîáàâèòü â íà÷àëî ñïèñêà
	int del_start(); //Óäàëåíèå ïåðâîãî ýë-òà ñïèñêà
	int del_back(); //óäàëåíèå ïîñëåäíåãî ýë-òà ñïèñêà
	void print_list();//Ïå÷àòü ñïèñêà
	void clear(); //î÷èñòêà è óäàëåíèå ñïèñêà
	void insert(int i, int data);//Äîáàâèòü ýëåìåíò íà i-îå ìåñòî
	void remove(int i);//óäàëåíèå
	int read(int i, int* x); //÷òåíèå i-ãî ýëåìåíòà
	int get_start(int *x);
	int find_elem(int x);


private:
	class node{//êàæäûé îòäåëüíûé ýëåìåíò ñïèñêà
	public:
		node *next;//óêàçàòåëü íà ñëåäóþùèé ýëåìåíò
		int data;//èíôîðìàöèîííîå ïîëå ýëåìåíòà ñïèñêà
		node(int data = 0, node *next = nullptr){//Êîíñòðóêòîð ñ ïàðàìåòðàìè
			this->data = data;
			this->next = next;
		}
	};

	node *head;//Óêàçàòåëü â ñïèñêè íà ãîëîâó
};

void list::push_back(int data)/*Äîáàâèòü â êîíåö ñïèñêà*/{
	if (head == nullptr)//Åñëè íè îäíîãî ÷èñëà â ñïèñêå
		head = new node(data);//Ñîçäàåì ãîëîâó è çàïèñûâàåì â íåå data
	else
	{
		node *curr = this->head;//Äëÿ ïåðåìåùåíèÿ ïî ñïèñêó
		while (curr->next != nullptr)//Ïåðåìåùàåìñÿ äî êîíöà ñïèñêà
			curr = curr->next;
		curr->next = new node(data);//Äîáàâëÿåì íîâûé ýëåìåíò ñïèñêà
	}
}
void list::push_front(int data)/*äîáàâèòü â íà÷àëî*/{
	node *old_head = head;//ñîçäàåì ïåðåìåííóþ ãäå õðàíèì ñòàðóþ ãîëîâó
	node *new_head = new node;//Ñîçäàåì íîâóþ ãîëîâó
	new_head->data = data;//ïðèñâàèâàåì åé èíô ïîëå
	new_head->next = old_head;//óêàçûâàåì next êàê ñòàðóþ ãîëîâó
	head = new_head;//çàìåíÿåì
}
int list::del_start()/*Èçâëå÷ü èç ãîëîâû*/{
	if (head == nullptr)//åñëè ñïèñîê ïóñò
		return 0;
	else
	{ 
		node *temp = head;//äëÿ õðàíåíèÿ ñòàðîé ãîëîâû
		head = head->next;
		delete temp;//óäàëÿåì ñòàðóþ ãîëîâó
		return 1;
	}
}
int list::del_back()/*Èçâëå÷åíèå èç êîíöà ñïèñêà*/{
	if (head == nullptr)//Åñëè ãîëîâà ïóñòà
		return 0;
	else
	{
		if (head->next == nullptr)
		{
			node* temp = head;
			head = nullptr;
			delete temp;
		}
		else
		{
			node *curr = head;//Äëÿ ïåðåìåùåíèÿ ïî ñïèñêó
			node *prev = nullptr;
			while (curr->next != nullptr)
			{
				prev = curr;
				curr = curr->next;
			}
			delete prev->next;
			prev->next = nullptr;
		}
		return 1;
	}
}
void list::print_list()/*Ïå÷àòü ñïèñêà*/{
	if (head == nullptr)//ïóñòîòà ñïèñêà
		cout << "List is empty" << endl;
	else
	{
		node *curr = head;//äëÿ ïåðåäâèæåíèÿ âíóòðè ñïèñêà
		while (curr != nullptr)//ïîêà î÷åðåäíîé ýëåìåíò ñïèñêà íå áóäåò íóëåâûì
		{
 			cout << curr->data << " "; //âûâîäèì èíô.ïîëå
			curr = curr->next;//ñäâèãàåìñÿ ïî ñïèñêó
		}
		cout << endl;
	}
}
void list::insert(int i, int data){
	if (i < 0)//åñëè áûë ââåä¸í îòðèöàòåëüíûé íîìåð ýëåìåíòà ñïèñêà
		cout << "An invalid item number." << endl;
	else
	{
		if (head == nullptr)//Åñëè âäðóã ãîëîâà ïóñòàÿ
			push_front(data);
		else
		{
			node *prev = head; //Äëÿ ïåðåäâèæåíèÿ âíóòðè ñïèñêà
			for (int count = 0; count < i - 1; count++)//Ïåðåäâèãàåìñÿ ïî âñåìó ñïèñêó
			{
				if (prev->next == nullptr)//Åñëè äîñòèãëè êîíöà ñïèñêà åù¸ äî äîñòèæåíèÿ íåîáõîäèìîãî íîìåðà
				{
					cout << "An invalid item number. The item was written to the end of the list" << endl;
					break;
				}
				prev = prev->next;//Ê ñëåä.ýëåìåíòó
			}
			if (i == 0)
			{
				push_front(data);//Àíàëîãè÷íî äîáàâëåíèþ â íà÷àëî ñïèñêà
			}
			else
			{
				node *new_node = new node; //ñîçäàåì íîâûé ýëåìåíò ñïèñêà
				new_node->data = data; //çàïèñûâàåì èíô ïîëå â äàííûé ýëåìåíò
				new_node->next = prev->next; //Ïîìåùàåì äàííûé ýëåìåíò ìåæäó i - 1 è i-ì
				prev->next = new_node;
			}
		}
	}
}
void list::remove(int i){
	if (i < 0 || head == nullptr)
		cout << "An invalid item number." << endl;
	else
	{
		node *curr = head;
		int size = 0;
		while (curr != nullptr)
		{
			curr = curr->next;
				size++;
		}
		curr = head;
		if (i == 0)
		{
			del_start();
			return;
		}
		if (i >= size)
			return;
		else
			for (int k = 0; k < i- 1; k++)
				curr = curr->next;
					if (i == size -1)
					{
						delete curr->next;
						curr->next = nullptr;
					}
					else
					{
						node *del = curr->next;
						curr->next = curr->next->next;
						delete del;
					}

		}
}
void list::clear(){
	while (head != nullptr)
		del_start();//Óäàëÿåì ïåðâûé ýëåìåíò ñïèñêà, ïîêà îí íå ñòàíåò íóëåâûì
}
int list::read(int i, int *x)/*Ïðî÷èòàòü i-é ýëåìåíò ñïèñêà*/{
	if (head != nullptr)
	{
		node *curr = head; //äëÿ äâèæåíèÿ ïî ñïèñêó
		bool check_empty = false;
		for (int k = 0; k < i; k++)
		{
			if (curr->next == nullptr)
			{
				check_empty = true;
				break;
			}
			curr = curr->next;
		}
		if (!check_empty)
		{
			*x = curr->data; //Âîçâðàùàåì çíà÷åíèÿ ïî íîìåðó i
			return 1;
		}
		else
			return 0;
	}
	else
		return 0;
}
int list::get_start(int *x){
	if (head == nullptr)
		return 0;
	else
	{
		node *temp = head;
		*x = head->data;
		head = head->next;
		delete temp;
		return 1;
	}
}
int list::find_elem(int x)/*Ïîèñê ïåðâîãî âõîæäåíèÿ ýëåìåíòà*/{
	int count = 0; //ñ÷èòàòü êàêîé ýëåìåíò ïî ñ÷¸òó ñîâïàë
	if (head != nullptr)
	{
		node *curr = head;
		while (curr != nullptr)
		{
			if (curr->data == x)
				return count;
			curr = curr->next;
			count++;
		}
		return -1;
	}
	else
		return -1;
}

int _tmain(int argc, _TCHAR* argv[])
{
	/*ofstream out("output.dat");//äëÿ çàïèñè ðåçóëüòàòà
	ifstream in("input.dat"); //äëÿ ÷òåíèÿ èñõîäíîãî ñïèñêà
	if (!(in.is_open())) //Åñëè ôàéë íå îòêðûò
	{
		cout << "File wasn't open" << endl;
		ofstream tmp("input.dat");//ñîçäàåì òàêîé æå ôàéë
		tmp.close();
	}
	else
	{
		cout << "File input.dat was successfully opened" << endl;
		int x; //î÷åðåäíîå ÷èñëî
		list *start_lst = new list();//ñîçäà¸ì ñïèñîê
		list *list_chet = new list();//Ñïèñîê ÷åòíûõ ýëåìåíòîâ
		list *dividing_by3 = new list();//Ñïèñîê äåëÿùèéñÿ íà 3
		
		//çàïîëíÿåì èñõîäíûé ñïèñîê
		while (in >> x)
		{
			start_lst->push_back(x);
		}
		if (!in.eof())
			cout << "File is broken. Error!" << endl;
		else
		{
			cout << "Starts list:" << endl;
			start_lst->print_list();//Ïå÷àòü èñõîäíîãî ñïèñêà

			//Ïðîõîäèì ïî èçíà÷àëüíîìó ñïèñêó è ôîðìèðóåì ïîäñïèñêè
			int i = 0; //ñ÷¸ò÷èê äëÿ ïðîõîäà ïî ñïèñêó
			while (start_lst->read(i, &x))//ïîêà ìû ìîæåì ñ÷èòûâàòü i-é ýëåìåíò ñïèñêà
			{
				bool check = true;//äëÿ ïðîâåðêè, âîøëî ëè ÷èñëî â ïîäñïèñîê èëè íåò
				if (x % 2 == 0)
				{
					list_chet->push_back(x);//çàíîñèì â ïîäñïèñîê
					check = false;
				}
				if (x % 3 == 0)
				{
					dividing_by3->push_back(x);//çàíîñèì â ïîäñïèñîê
					check = false;
				}
				if (!check)
					start_lst->remove(i);//óäàëÿåì ýëåìåíò, åñëè îí âîø¸ë õîòÿ áû â îäèí ïîäñïèñîê
				else
					i++;//Â äðóãîì ñëó÷àå ïåðåõîäèì íà ñëåäóþùèé ýëåìåíò ñïèñêà
			}
			
			//Ïå÷àòü íà ýêðàí è çàïèñü ðåçóëüòèðóþùèõ ñïèñêîâ â ôàéë
			cout << "\nResult of programme is: " << endl;
			cout << "List of numbers that divided by 3: " << endl;
			dividing_by3->print_list();//Ïå÷àòü ñïèñêà ýëåìåíòîâ êðàòíûõ òð¸ì
			while (dividing_by3->get_start(&x))//çàïèñü â ôàéë ñïèñêà /3
				out << x << " ";
			out << "\n";
			cout << "List of even numbers: " << endl;
			list_chet->print_list();//ïå÷àòü ñïèñêà ÷åòíûõ ýëåìåíòîâ
			while (list_chet->get_start(&x))//çàïèñü â ôàéë ñïèñêà ÷åòíûõ ÷èñåë
				out << x << " ";
			out << "\n";
			cout << "List of other numbers: " << endl;
			start_lst->print_list();//ïå÷àòü ýëåìåíòîâ îñòàâøèõñÿ â ñïèñêå
			while (start_lst->get_start(&x))//çàïèñü â ôàéë îñòàëüíûõ ÷èñåë
				out << x << " ";

			delete start_lst;//Îñâîáîæäàåì ïàìÿòü
			delete list_chet;//îñâîáîæäàåì ïàìÿòü
			delete dividing_by3;//îñâîáîæäàåì ïàìÿòü
		}
	}
	in.close();//çàêðûâàåì ôàéëû
	out.close();
	*/
	list a;
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);
	a.remove(2);
	a.print_list();
	return 0;
}


//Определить, являются ли заданные точки вершинами выпуклого многоугольника. 
//Перечислить их в порядке обхода вершин по или против часовой стрелки, если являются
#pragma once
#include <vector>
#include <string>
#include <stack>
#include "PointG.h"

namespace ALG_3_8 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	class Point;
	public ref class MyForm : public System::Windows::Forms::Form
	{
	private:
		vector<PointG> *points;			//массив точек
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  NamePoint;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  X;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Y;
	private: System::Windows::Forms::Button^  buttonDelete;
	private: System::Windows::Forms::Button^  buttonSearch;

	string *currLetter;				//текущая буква для точки
	private: Bitmap ^screen;
			 Graphics ^graph;

	void getCurrLetter(){//подсчёт текущей буквы
			int length = currLetter->length(); //длина строки имени
			int curr = length - 1;
			if (currLetter->at(curr) == 'Z'){
				while (curr >= 0 && currLetter->at(curr) == 'Z'){
					currLetter->at(curr) = 'A';
					curr--;
				}
				if (curr >= 0)
					currLetter->at(curr) = currLetter->at(curr) + 1;
				else
				{
					*currLetter = "A" + *currLetter;
				}
			}
			else
				currLetter->at(length - 1) = currLetter->at(length - 1) + 1;
		}
	void pointToScreenCoord(double x, double y, double *newX, double *newY){//перевод координатов точек в в экранные
		*newX = x + 200;
		*newY = -y + 200;
	}
	int orientation(PointG A, PointG B, PointG C){//функция вычисляет направление векторного произведения
		int orientation = (B.getX() - A.getX())*(C.getY() - B.getY()) - (B.getY() - A.getY())*(C.getX() - B.getX());
		return orientation;
	}
	PointG PreLast(stack<int> &st){//возвращает предпоследний элемент из стека
		int top = st.top();//получаем элемент и вершины
		st.pop();//извлекаем его
		PointG prelastpoint = points->at(st.top());//получаем точку, соответствующую предпоследней позиции в стеке
		st.push(top);//возвращаем в стек старую точку
		return prelastpoint;
	}
	int distance(PointG a, PointG b)//возвращает расстояние расстояние между векторами a и b
	{
		return (b.getX() - a.getX())*(b.getX() - a.getX()) + (b.getY() - a.getY())*(b.getY() - a.getY());
	}
	public:
		MyForm(void)
		{
			InitializeComponent();
		}

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureField;
	private: System::Windows::Forms::DataGridView^  tablePoints;
	private: System::Windows::Forms::Label^  labelMain;

	private: System::Windows::Forms::TextBox^  textBoxX;
	private: System::Windows::Forms::TextBox^  textBoxY;
	private: System::Windows::Forms::Button^  buttonAdd;
	private: System::Windows::Forms::Label^  labelX;
	private: System::Windows::Forms::Label^  label2;
	protected:

	private:
		/// <summary>
		/// Требуется переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->pictureField = (gcnew System::Windows::Forms::PictureBox());
			this->tablePoints = (gcnew System::Windows::Forms::DataGridView());
			this->NamePoint = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->X = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Y = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->labelMain = (gcnew System::Windows::Forms::Label());
			this->textBoxX = (gcnew System::Windows::Forms::TextBox());
			this->textBoxY = (gcnew System::Windows::Forms::TextBox());
			this->buttonAdd = (gcnew System::Windows::Forms::Button());
			this->labelX = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->buttonDelete = (gcnew System::Windows::Forms::Button());
			this->buttonSearch = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureField))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tablePoints))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureField
			// 
			this->pictureField->BackColor = System::Drawing::SystemColors::Window;
			this->pictureField->Location = System::Drawing::Point(4, 2);
			this->pictureField->Name = L"pictureField";
			this->pictureField->Size = System::Drawing::Size(420, 420);
			this->pictureField->TabIndex = 0;
			this->pictureField->TabStop = false;
			// 
			// tablePoints
			// 
			this->tablePoints->AllowUserToAddRows = false;
			this->tablePoints->AllowUserToDeleteRows = false;
			this->tablePoints->AllowUserToResizeColumns = false;
			this->tablePoints->AllowUserToResizeRows = false;
			this->tablePoints->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->tablePoints->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {
				this->NamePoint,
					this->X, this->Y
			});
			this->tablePoints->Location = System::Drawing::Point(430, 255);
			this->tablePoints->MultiSelect = false;
			this->tablePoints->Name = L"tablePoints";
			this->tablePoints->RowHeadersVisible = false;
			this->tablePoints->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->tablePoints->Size = System::Drawing::Size(220, 150);
			this->tablePoints->TabIndex = 10;
			this->tablePoints->SelectionChanged += gcnew System::EventHandler(this, &MyForm::tablePoints_SelectionChanged);
			// 
			// NamePoint
			// 
			this->NamePoint->Frozen = true;
			this->NamePoint->HeaderText = L"Название";
			this->NamePoint->Name = L"NamePoint";
			this->NamePoint->ReadOnly = true;
			// 
			// X
			// 
			this->X->Frozen = true;
			this->X->HeaderText = L"X";
			this->X->Name = L"X";
			this->X->ReadOnly = true;
			this->X->Width = 50;
			// 
			// Y
			// 
			this->Y->Frozen = true;
			this->Y->HeaderText = L"Y";
			this->Y->Name = L"Y";
			this->Y->ReadOnly = true;
			this->Y->Width = 50;
			// 
			// labelMain
			// 
			this->labelMain->AutoSize = true;
			this->labelMain->Location = System::Drawing::Point(450, 20);
			this->labelMain->MaximumSize = System::Drawing::Size(200, 150);
			this->labelMain->Name = L"labelMain";
			this->labelMain->Size = System::Drawing::Size(52, 13);
			this->labelMain->TabIndex = 8;
			this->labelMain->Text = L"labelMain";
			// 
			// textBoxX
			// 
			this->textBoxX->Location = System::Drawing::Point(474, 173);
			this->textBoxX->Name = L"textBoxX";
			this->textBoxX->Size = System::Drawing::Size(69, 20);
			this->textBoxX->TabIndex = 0;
			this->textBoxX->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::textBoxX_KeyPress);
			// 
			// textBoxY
			// 
			this->textBoxY->Location = System::Drawing::Point(549, 173);
			this->textBoxY->Name = L"textBoxY";
			this->textBoxY->Size = System::Drawing::Size(70, 20);
			this->textBoxY->TabIndex = 1;
			this->textBoxY->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::textBoxX_KeyPress);
			// 
			// buttonAdd
			// 
			this->buttonAdd->Location = System::Drawing::Point(505, 199);
			this->buttonAdd->Name = L"buttonAdd";
			this->buttonAdd->Size = System::Drawing::Size(75, 23);
			this->buttonAdd->TabIndex = 2;
			this->buttonAdd->Text = L"Добавить";
			this->buttonAdd->UseVisualStyleBackColor = true;
			this->buttonAdd->Click += gcnew System::EventHandler(this, &MyForm::buttonAdd_Click);
			// 
			// labelX
			// 
			this->labelX->AutoSize = true;
			this->labelX->Location = System::Drawing::Point(471, 157);
			this->labelX->Name = L"labelX";
			this->labelX->Size = System::Drawing::Size(77, 13);
			this->labelX->TabIndex = 6;
			this->labelX->Text = L"Координата X";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(546, 157);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(77, 13);
			this->label2->TabIndex = 7;
			this->label2->Text = L"Координата Y";
			// 
			// buttonDelete
			// 
			this->buttonDelete->Location = System::Drawing::Point(505, 228);
			this->buttonDelete->Name = L"buttonDelete";
			this->buttonDelete->Size = System::Drawing::Size(75, 23);
			this->buttonDelete->TabIndex = 4;
			this->buttonDelete->Text = L"Удалить";
			this->buttonDelete->UseVisualStyleBackColor = true;
			this->buttonDelete->Click += gcnew System::EventHandler(this, &MyForm::buttonDelete_Click);
			// 
			// buttonSearch
			// 
			this->buttonSearch->Location = System::Drawing::Point(494, 106);
			this->buttonSearch->Name = L"buttonSearch";
			this->buttonSearch->Size = System::Drawing::Size(100, 25);
			this->buttonSearch->TabIndex = 11;
			this->buttonSearch->Text = L"Поиск";
			this->buttonSearch->UseVisualStyleBackColor = true;
			this->buttonSearch->Click += gcnew System::EventHandler(this, &MyForm::buttonSearch_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(664, 421);
			this->Controls->Add(this->buttonSearch);
			this->Controls->Add(this->buttonDelete);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->labelX);
			this->Controls->Add(this->buttonAdd);
			this->Controls->Add(this->textBoxY);
			this->Controls->Add(this->textBoxX);
			this->Controls->Add(this->labelMain);
			this->Controls->Add(this->tablePoints);
			this->Controls->Add(this->pictureField);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"MyForm";
			this->Text = L" ";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &MyForm::MyForm_FormClosed);
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureField))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tablePoints))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:System::Void textBoxX_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
		char symb = e->KeyChar;
		if ((symb >= 48 && symb <= 59) || symb == 8 || symb == ',' || symb == '-')
			return;
		else
			e->Handled = true;
	}
	System::Void buttonAdd_Click(System::Object^  sender, System::EventArgs^  e) {
	textBoxX->Focus();
	try
	{
		if (textBoxX->Text != "" && textBoxY->Text != "")//проверка на корректность ввода
		{
			double x = Convert::ToDouble(textBoxX->Text);
			double y = Convert::ToDouble(textBoxY->Text);
			if (Math::Abs(x) > 200 || Math::Abs(y) > 200)
				MessageBox::Show("Пожалуйста, введите числа, меньшие по модулю 200, чтобы их точки влезли в график", "Please", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			else
			{
				String^ stroka = gcnew String(currLetter->c_str());  //получение наименования для точки
				PointG point(x, y, *currLetter);
				points->push_back(point); //занесение точки в список
				getCurrLetter(); //обновление наименования для точки

				//добавления строчки в таблицу
				tablePoints->Rows->Add(stroka, x, y);
				DrawPoint(point);
			}
		}
	}
	catch (...){
		MessageBox::Show("Ошибочные введённые данные!", "ОШИБКА", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}
	System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
	screen = gcnew Bitmap(pictureField->Width, pictureField->Height);
	graph = Graphics::FromImage(screen);
	buttonDelete->Enabled = false;
	points = new vector<PointG>;
	currLetter = new string("A"); //наименование точек начинается с 'A'
	labelMain->Text = "Вводите точки, а затем нажмите Искать для получения ответа о многоугольнике";
	DrawCoordinated();//отрисовать систему координат
}
	System::Void MyForm_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
	delete points;
}
	System::Void buttonDelete_Click(System::Object^  sender, System::EventArgs^  e) {//удаление из таблицы и из массива
	int index = tablePoints->SelectedCells[0]->RowIndex; //вычисляем выделенную строку
	points->erase(points->begin() + index);//удаляем из вектора точек
	tablePoints->Rows->RemoveAt(index);//удаляем из таблицы
	graph->Clear(Color::White);//очищаем график
	DrawCoordinated();//перерисовываем координаты
	for (auto it = points->begin(); it != points->end(); it++)
		DrawPoint(*it);//и рисуем по новой все точки

}
	System::Void tablePoints_SelectionChanged(System::Object^  sender, System::EventArgs^  e) {
	if (tablePoints->SelectedCells->Count > 0)
		buttonDelete->Enabled = true;
	else
		buttonDelete->Enabled = false;
}
	void DrawCoordinated(){//рисует оси x и у
	screen = gcnew Bitmap(pictureField->Width, pictureField->Height);
	graph = Graphics::FromImage(screen);
	graph->TextRenderingHint = Drawing::Text::TextRenderingHint::AntiAlias;
	Pen ^pencil = gcnew Pen(Color::Black, 1);
	FontFamily ^f = gcnew FontFamily("Courier New");
	SolidBrush ^blackbrush = gcnew SolidBrush(Color::Black);
	Drawing::Font ^newfont = gcnew Drawing::Font(f, 11, FontStyle::Bold);

	//наименования осей
	graph->DrawString("Y", newfont, blackbrush, 205, 0);
	graph->DrawString("X", newfont, blackbrush, 395, 180);
	//оси
	graph->DrawLine(pencil, 200, 0, 200, 400);
	graph->DrawLine(pencil, 0, 200, 400, 200);
	//стрелочки на осях
	graph->DrawLine(pencil, 200, 0, 195, 10);
	graph->DrawLine(pencil, 200, 0, 205, 10);
	graph->DrawLine(pencil, 400, 200, 393, 195);
	graph->DrawLine(pencil, 400, 200, 393, 205);

	pictureField->Image = screen;
}
	void DrawPoint(PointG point){//рисует точку point
	Pen ^pencil = gcnew Pen(Color::Red, 1);
	Drawing::Font ^newfont = gcnew Drawing::Font("TimesNewRoman", 15, FontStyle::Bold, GraphicsUnit::Pixel);
	SolidBrush ^blackbrush = gcnew SolidBrush(Color::Black);
	SolidBrush ^redbrush = gcnew SolidBrush(Color::Red);

	//перевод координаты точки в экранные
	double x, y;
	pointToScreenCoord(point.getX(), point.getY(), &x, &y);

	//вывод точки на экране
	graph->FillEllipse(redbrush, x - 4, y - 4, 8, 8);
	String^ str = gcnew String(point.getName().c_str());
	graph->DrawString(str, newfont, blackbrush, x + 8, y- 8);
	pictureField->Image = screen;
}
	void DrawEdge(PointG point1, PointG point2){//рисует ребро между point1 и point2
		Pen ^edgePen = gcnew Pen(Color::Blue, 2);
		double x1, y1; pointToScreenCoord(point1.getX(), point1.getY(), &x1, &y1);
		double x2, y2; pointToScreenCoord(point2.getX(), point2.getY(), &x2, &y2);
		graph->DrawLine(edgePen, (int)x1, (int)y1, (int)x2, (int)y2);
	}
	vector <PointG> formList(){
		int size = points->size();
		vector<PointG> convexHull;
		vector<int>* indexingSort = new vector<int>(size); //будет содержать индексы точек при сортировке их по углу
		for (int i = 0; i < size; i++)
			indexingSort->at(i) = i;
		//Нахождение точки с самой маленькой Y и самой левой X при равенстве Y
		int minPoint = 0;//изначально минимальная точка - первая в массиве
		double minY = points->at(0).getX();
		double minX = points->at(0).getY();
		for (int i = 1; i < size; i++)
			if (points->at(i).getY() <= minY)//если у точки меньше или равна y
			{
				if (points->at(i).getY() == minY)//если равна
				{
					if (points->at(i).getX() <= minX)//то сравниваем x
					{
						minPoint = i;//заменяем самую левую-нижнюю точку
						minX = points->at(i).getX();
						minY = points->at(i).getY();
					}
				}
				else//иначе, если y меньше у текущей точки
				{
					minPoint = i;//заменяем самую левую-нижнюю точку
					minX = points->at(i).getX();
					minY = points->at(i).getY();
				}
			}
		
		//Переносим  минимальный индекс в начало списка
		indexingSort->at(0) = minPoint;
		indexingSort->at(minPoint) = 0;

		String ^str = gcnew String(points->at(minPoint).getName().c_str());

		//Сортируем все точки по углу между начальной точкой с minIndex
		for (int i = 1; i < size; i++)
		{
			int	j = i;
			while (j > 0 && //сортируем вставкой минимального элемента в начало текущего отсортированного массива
				//если minPoint, j-1-ая и j-ая точки образуют поворот по часовой стрелке
				(orientation(points->at(minPoint), points->at(indexingSort->at(j - 1)), points->at(indexingSort->at(j))) < 0))
			{
				int tmp = indexingSort->at(j);
				indexingSort->at(j) = indexingSort->at(j - 1);
				indexingSort->at(j - 1) = tmp;
				j -= 1;
			}
		}

		stack<int> *addedToHull = new stack<int>();//стек для минимальной выпуклой оболочки
		int maxDistance = 0;
		int numMaxDistance = 0;
		int i = 0;
		//добавляем в стек вершины, которые гарантированно входят в оболочку
		addedToHull->push(minPoint);

		//проверяем начало списка на случай, если 3 и более вершины лежат на одной прямой с начальной точкой
		for (i = 0; i < indexingSort->size() - 1; i++)
			if (orientation(points->at(minPoint), points->at(indexingSort->at(i)), points->at(indexingSort->at(i + 1))) == 0)//углы равны
			{
				int d = distance(points->at(minPoint), points->at(indexingSort->at(i+1)));//вычисляем расстояние до начала
				if (d > maxDistance)//если оно превосходит текущее максимальное
				{
					maxDistance = d;//изменяем его на новое
					numMaxDistance = i+1;
				}
			}
			else
				break;
		//проставляем индексы -1 вершинам, лежащим на той же прямой, что и начальная
		//кроме самой удалённой
		for (int k = 1; k < i+1; k++)
			if (k != numMaxDistance)
				indexingSort->at(k) = -1;
		if (size - i > 1)
		{
			//добавляем её в стек
			addedToHull->push(indexingSort->at(numMaxDistance));
			//проходим по всему списку
			for (int i = numMaxDistance + 1; i < size; i++)
			{
				if (indexingSort->at(i) != -1)
				{
					//пока вершины образуют правую тройку
					while (orientation(PreLast(*addedToHull), points->at(addedToHull->top()), points->at(indexingSort->at(i))) < 0)
						addedToHull->pop();//извлекаем из стека
					addedToHull->push(indexingSort->at(i));//заносим в стек новую вершину
				}
			}
		}
		//записываем точки из стека в вектор
		while (addedToHull->empty() == false){
			convexHull.push_back(points->at(addedToHull->top()));
			addedToHull->pop();
		}
		return convexHull;
	}
	void getAnswer(vector<PointG> vect){//вывод ответа на задачу, и вывод точек в случае положительного ответа
		if (vect.size() == points->size())//все точки образуют выпуклый многоугольник, если они все входят в выпуклую оболочку
		{
			String ^resString = "Полученный многоугольник: "; //вывод информации о полученном многоугольнике
			for (auto it = vect.begin(); it != vect.end(); it++)
				resString += (gcnew String(it->getName().c_str()));
			labelMain->Text = resString;
		}
		else//иначе нельзя получить выпуклый многоугольник
		{
			labelMain->Text = "Из данного набора точек нельзя получить выпуклый многоугольник";
		}
	}
private: System::Void buttonSearch_Click(System::Object^  sender, System::EventArgs^  e) {
	if (points->size() < 3) //для меньше, чем трёх точек выпуклую оболочку бессмысленно строить
		MessageBox::Show("Точек должно быть хотя бы 3", "Внимание", MessageBoxButtons::OK, MessageBoxIcon::Warning);
	else{
		//формируем массив точек, которые входят в выпуклую оболочку
		vector<PointG> vect = formList();
		//перерисовываем точки
		graph->Clear(Color::White);//очищаем график
		DrawCoordinated();//перерисовываем координаты
		for (auto it = points->begin(); it != points->end(); it++)
			DrawPoint(*it);//и рисуем по новой все точки

		if (vect.size() < 3)//если в ответе меньше 3 вершин
		{
			getAnswer(vect);//сразу выдаем ответ
		}
		else
		{//в ответе хотя бы 3 вершины
			//выводим на экран рёбра между этими точками
			PointG firstP = vect.at(0);
			PointG secondP = vect.at(1);
			for (auto it = vect.begin() + 2; it != vect.end(); it++)
			{
				DrawEdge(firstP, secondP);
				firstP = secondP;
				secondP = *it;
			}
			DrawEdge(firstP, secondP);
			DrawEdge(vect.at(0), secondP);
			pictureField->Image = screen;//выводим полотно на экран

			getAnswer(vect);//получение ответа на задачу
		}
	}
}
};
}
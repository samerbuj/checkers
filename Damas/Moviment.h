#pragma once
#include <iostream>
using namespace std;

class Moviment
{
public:

	Moviment();
	~Moviment();

	const int getFO() { return M_FilaOrigen; };
	const int getCO() { return M_ColumnaOrigen; };
	const int getFD() { return M_FilaDesti; };
	const int getCD() { return M_ColumnaDesti; };

	void setFO(int FO) { M_FilaOrigen = FO; };
	void setCO(int CO) { M_ColumnaOrigen = CO; };
	void setFD(int FD) { M_FilaDesti = FD; };
	void setCD(int CD) { M_ColumnaDesti = CD; };

private:

	int M_FilaOrigen, M_ColumnaOrigen, M_FilaDesti, M_ColumnaDesti;

};
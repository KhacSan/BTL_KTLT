#include<vector>
#include<fstream>
#include<string>
#include<iomanip>
#include <cstdlib>
#include<iostream>
using namespace std;

typedef struct thoiGian {
	string ngayThangNam;
	int gioDen;
	int phutDen;
	int gioVe;
	int phutVe;
}ThoiGian;

typedef struct nhanvien{
	string ho;
	string ten;
	string maNhanVien;
	string donVi;
	string chucVu;
	string ngaySinh;
	string queQuan;
	string diaChi;
	string email;
	string sdt;
	string ngayBatDauLamViec;
	vector <ThoiGian> DS_ThoiGianLamViec;
}NhanVien;

//đọc thời gian làm việc của 1 nhân viên
void DocThoiGianLamViec(ifstream &input,ThoiGian &ThoiGianLamViec) {
	
	getline(input, ThoiGianLamViec.ngayThangNam,',');
	input >> ThoiGianLamViec.gioDen;
	input.seekg(1,1); //dich con tro chi vi 1 byte
	input >> ThoiGianLamViec.phutDen;
	input.seekg(1, 1);
	input >> ThoiGianLamViec.gioVe;
	input.seekg(1, 1);
	input >> ThoiGianLamViec.phutVe;
}

// so sánh 2 ki tu dau tien cua 2 chuoi chuỗi 
int nemcmp(string str1, string str2) {
	for (int i = 0; i < 2; i++)
	{
		if (str1[i] > str2[i])
			return 1;
		else if (str1[i] < str2[i])
			return -1;
	}
	return 0;
}

//đọc thông tin 1 nhân viên từ file
void DocThongTinMotNhanVien(ifstream &input,NhanVien &nhanvien) {
	int n = 0,count =0;
	getline(input,nhanvien.maNhanVien);// doc vào dòng đâu tiên - mã nhân viên
	getline(input, nhanvien.ho);
	getline(input, nhanvien.ten);
	getline(input, nhanvien.donVi);
	getline(input, nhanvien.chucVu);
	getline(input, nhanvien.ngaySinh);
	getline(input, nhanvien.queQuan);
	getline(input, nhanvien.diaChi);
	getline(input, nhanvien.email);
	getline(input, nhanvien.sdt);
	getline(input, nhanvien.ngayBatDauLamViec);

	string temp;
	int vitri = input.tellg();// lay vi tri hien tai cua con tro
	while (true)
	{
		
		if (input.eof()) break;
		getline(input, temp);
		if(nemcmp(temp, "NV") == 0 ) break;
		n++;
	}

	// dich chuyen con tro den vi tri = vitri
	input.seekg(vitri, ios::beg);
	ThoiGian thoiGianLamViec;

	while (count < n )
	{
		DocThoiGianLamViec(input, thoiGianLamViec);
		getline(input, temp);
		nhanvien.DS_ThoiGianLamViec.push_back(thoiGianLamViec);
		count++;
	}

}

void xuatThoiGian(ThoiGian thoiGian) {
	cout << "Ngay : " << thoiGian.ngayThangNam << "," << thoiGian.gioDen << ":" << thoiGian.phutDen << "," 
		 << thoiGian.gioVe << ":" << thoiGian.phutVe << endl;
}

void xuatThongTinMotNhanVien(NhanVien nhanvien) {
	
	cout << "Ho: " << nhanvien.ho << endl;
	cout << "Ten: " << nhanvien.ten << endl;
	cout << "Ma nhan vien: " << nhanvien.maNhanVien << endl;
	cout << "Don vi: " << nhanvien.donVi << endl;
	cout << "Chuc vu: " << nhanvien.chucVu << endl;
	cout << "Ngay sinh: " << nhanvien.ngaySinh << endl;
	cout << "Que quan: " << nhanvien.queQuan << endl;
	cout << "Dia chi: " << nhanvien.diaChi << endl;
	cout << "Email: " << nhanvien.email << endl;
	cout << "SDT: " << nhanvien.sdt << endl;
	cout << "Ngay bat dau lam viec: " << nhanvien.ngayBatDauLamViec << endl;

	for (int i = 0; i < nhanvien.DS_ThoiGianLamViec.size(); i++) {
		xuatThoiGian(nhanvien.DS_ThoiGianLamViec[i]);
	}
}

typedef struct node_NhanVien {
	NhanVien nhanVien;
	node_NhanVien *next;
}Node_NhanVien;

typedef struct donVi {
	string tenDonVi;
    Node_NhanVien *canBo;
	Node_NhanVien *nhanVien;
	struct donVi *next;
	int soNhanVien;
}DonVi;

void create_LinkList_DonVi(DonVi *&ds_DonVi) {
	ds_DonVi = NULL;
}

void creat_DonVi(DonVi *&donVi,Node_NhanVien *nodeNhanVien) {
	donVi->tenDonVi = nodeNhanVien->nhanVien.donVi;
	if (_stricmp(((nodeNhanVien->nhanVien).chucVu).c_str(),"Nhan vien") == 0) { //c_str chuyen ve mang char
		donVi->nhanVien = nodeNhanVien;
		donVi->canBo = NULL;
		donVi->soNhanVien = 1;
	}
	else
	{
		donVi->canBo = nodeNhanVien;
		donVi->nhanVien = NULL;
		donVi->soNhanVien = 0;
	}
	donVi->next = NULL;
}

// tao ra một đơn vị mới nếu trong danh sách các đơn vị chưa có đơn vị la đơn vi làm viêc của nhân viên được thêm vào 
//và thêm nhân viên đó vào đơn vị này

void ThemMotDonVi(DonVi *donVi, DonVi *&ds_DonVi) {
	if (ds_DonVi == NULL) {
		ds_DonVi = donVi;
		ds_DonVi->next = ds_DonVi;
	}
	else {
		DonVi *p = ds_DonVi;
		while (true)
		{
			if (p->next == ds_DonVi) break;
			p = p->next;
		}
		p->next = donVi;
		donVi->next = ds_DonVi;
	}
}

// thêm 1 nhân viên mới
void Insert(DonVi *&ds_DonVi, Node_NhanVien *nodeNhanVien) {
	int count = 0;
	if (ds_DonVi != NULL) {
		DonVi *p = ds_DonVi;
		while (true)
		{
			if (_stricmp((p->tenDonVi).c_str(), ((nodeNhanVien->nhanVien).donVi).c_str()) == 0) {
				Node_NhanVien *pNode;
				count++;
				if (_stricmp(((nodeNhanVien->nhanVien).chucVu).c_str(), "nhan vien") == 0) {
					p->soNhanVien += 1;
					if (p->nhanVien == NULL) {
						p->nhanVien = nodeNhanVien;
						break;
					}
					else
					{
						pNode = p->nhanVien;
						p->nhanVien = nodeNhanVien;
						nodeNhanVien->next = pNode;
						break;
					}
				}
				else
				{
					if (p->canBo == NULL) {
						p->canBo = nodeNhanVien;
						break;
					}
					else
					{
						pNode = p->canBo;
						p->canBo = nodeNhanVien;
						nodeNhanVien->next = pNode;
						break;
					}
				}
			}
			if (p->next == ds_DonVi) break;
			p = p->next;
		}
	}
	if (count == 0 || ds_DonVi == NULL) {
		DonVi *donVi = new DonVi;
		creat_DonVi(donVi, nodeNhanVien);
		ThemMotDonVi(donVi, ds_DonVi);
	}
}

// đọc thông tin từ file NhanVien.txt
void DocFile(ifstream &input, DonVi *&ds_DonVi) {

	while (input.eof() == false)
	{
		NhanVien nhanvien;
		DocThongTinMotNhanVien(input, nhanvien);
		Node_NhanVien *nodeNhanVien = new Node_NhanVien;
		nodeNhanVien->nhanVien = nhanvien;
		nodeNhanVien->next = NULL;
		Insert(ds_DonVi, nodeNhanVien);
	}

}

// xuat toàn bộ thông tin đọc được từ file
void Output(DonVi *ds_DonVi) {
	
	if (ds_DonVi == NULL) return;
	else
	{
		DonVi *pDonVi = ds_DonVi;
		while (true)
		{
			Node_NhanVien *pCanBo = pDonVi->canBo;
			while (true) 
			{
				
				if (pCanBo == NULL) break;
				xuatThongTinMotNhanVien(pCanBo->nhanVien);
				pCanBo = pCanBo->next;
			}
			Node_NhanVien *pNhanVien = pDonVi->nhanVien;
			while (true)
			{
				
				if (pNhanVien == NULL) break;
				xuatThongTinMotNhanVien(pNhanVien->nhanVien);
				pNhanVien = pNhanVien->next;
			}
			if (pDonVi->next == ds_DonVi)
			{
				break;
			}
			pDonVi = pDonVi->next;
		}
	}
	



}

void xuatThongTinCoBanVeMotDonVi(DonVi *ds_DonVi, string tenDonVi) 
{
	DonVi *p = ds_DonVi;
	int count = 0;
	while (true)
	{
		if (_stricmp((p->tenDonVi).c_str(), tenDonVi.c_str()) == 0) {
			count++;
			int n = 0;   //bien dem so can bo
			cout << "Danh sach Can Bo: " << endl;
			Node_NhanVien *pCanBo = p->canBo;
			while (true)
			{
				if (pCanBo == NULL) {
					break;
				}
				else
				{
					n++;
					xuatThongTinMotNhanVien(pCanBo->nhanVien);
					pCanBo = pCanBo->next;
				}
			}
			if (n == 0) cout << "Khong co thong tin can bo!" << endl;
			int m = 0;    //bien dem so nhan vien
			cout << "Danh Sach Nhan Vien: " << endl;
			Node_NhanVien *pNhanVien = p->nhanVien;
			while (true)
			{
				if (pNhanVien == NULL) {
					break;
				}
				else
				{
					m++;
					xuatThongTinMotNhanVien(pNhanVien->nhanVien);
					pNhanVien = pNhanVien->next;
				}
			}
			if (m == 0) cout << "Khong co thong tin nhan vien!" << endl;
		}
		if (p->next == ds_DonVi) break;
		p = p->next;
	}
	if (count == 0) {
		cout << "Khong co don vi nay trong danh sach!" << endl;
	}
}

void XuatThongTinCoBanVeCongTy(DonVi *ds_DonVi) {
		DonVi *p = ds_DonVi;
		int TongSoNhanVien = 0;
		if (ds_DonVi == NULL) return;
		else
		{
			while (true)
			{
				TongSoNhanVien += p->soNhanVien;
				Node_NhanVien *pCanBo = p->canBo;
				cout << p->tenDonVi << " : " << endl;
				cout << left << setw(15) << "Ho" << setw(10) << "Ten" << setw(10) << "Chuc Vu" << endl;
				while (true)
				{
					if (pCanBo == NULL) break;
					cout << left << setw(15) << pCanBo->nhanVien.ho << setw(10) << pCanBo->nhanVien.ten
						<< setw(10) << pCanBo->nhanVien.chucVu << endl;
					pCanBo = pCanBo->next;
				}
				if (p->next == ds_DonVi) break;
				p = p->next;
			}
			cout << "Tong So Nhan Vien = " << TongSoNhanVien << endl;
		}
}
/*
void Search(DonVi *ds_DonVi, string giaTriTimKiem) {


}

void HienThiTrangThaiLamViec(DonVi *ds_DonVi, string manv) {


}

void UpdateInfo_NhanVien(DonVi *ds_DonVi, NhanVien nhanVien) {


}
*/

int main()
{
	ifstream input;
	input.open("NhanVien.txt", ios_base::in);
	DonVi *ds_DonVi;
	create_LinkList_DonVi(ds_DonVi);
	DocFile(input, ds_DonVi);
	int Lua_Chon;
	do
	{ 
		cout << "-------------------------------------------menu----------------------------------------------"<<endl;
		cout << "1. Hien thi cac thong tin co ban ve BKCorporation?" << endl;
		cout << "2. Tim kiem thong tin cua nhan vien?" << endl;
		cout << "3. Hien thi tinh trang lam viec cua nhan vien?" << endl;
		cout << "4. Hien thi thong tin cua mot don vi?" << endl;
		cout << "5. Them nhan vien moi?" << endl;
		cout << "6. Cap nhat thong tin co ban cua mot nhan vien?" << endl;
		cout << "7. Thoat!" << endl;
		cout << "Ban chon: ";

		if (cin.fail()) { //neu khong phai la so nguyen
			cin.clear(); // bo qua co loi
			cin.ignore(32767, '\n'); //xoa di tat ca cac ki tu trong bo nho dem den khi gap \n
		}

		cin >> Lua_Chon;
		switch (Lua_Chon)
		{
			case 1: {
				system("cls");
				cout << "Thong tin co ban ve cong ty BKCorporation: ";
				XuatThongTinCoBanVeCongTy(ds_DonVi);
				break;
			}
			case 2: {
				break;
			}
			case 3: {
				break;
			}
			case 4: {
				system("cls");
				string tenDonVi;
				cout << "Nhap ten don vi can tim: ";
				cin.ignore();
				getline(cin, tenDonVi);
				xuatThongTinCoBanVeMotDonVi(ds_DonVi, tenDonVi);
				break;
			}
			case 5: {
				system("cls");
				NhanVien nhanVien;
				cout << "Nhap Thong tin nhan vien can them: "<<endl;

				cout << "Ho: "; 
				cin.ignore();//xoa bo bo dem
				getline(cin, nhanVien.ho);
				
				cout << "Ten: ";
				cin.sync();   //xoa bo dem
				getline(cin, nhanVien.ten);
				
				cout << "Ma nhan vien: " ;
				cin.sync();
				getline(cin, nhanVien.maNhanVien);
			
				cout << "Don vi: " ;
				cin.sync();
				getline(cin, nhanVien.donVi);

				cout << "Chuc vu: " ;
				cin.sync();
				getline(cin, nhanVien.chucVu);
			
				cout << "Ngay thang nam sinh : ";
				cin.sync();
				getline(cin, nhanVien.ngaySinh);
				
				cout << "Que quan: ";
				cin.sync();
				getline(cin, nhanVien.queQuan);
				
				cout << "Dia chi: " ;
				cin.sync();
				getline(cin, nhanVien.diaChi);
				
				cout << "Email: ";
				cin.sync();
				getline(cin, nhanVien.email);
				
				cout << "So dien thoai: ";
				cin.sync();
				getline(cin, nhanVien.sdt);
				
				cout << "Ngay bat dau lam viec: " ;
				cin.sync();
				getline(cin, nhanVien.ngayBatDauLamViec);
				char ch;
				cout << "Nhap gian lam viec (y/n)?" ;
				cin >> ch;
				if (ch == 'y' || ch == 'Y') {
					cout << "Nhap thoi gian lam viec:" << endl;
					while (true)
					{
						ThoiGian thoiGian;
						
						cout << "Ngay lam viec: ";
						cin.ignore();
						getline(cin,thoiGian.ngayThangNam);
						cout << "Thoi gian bat dau: "<<endl;
						cout << "Thoi gian den (gio phut): ";
						cin >> thoiGian.gioDen>>thoiGian.phutDen;
						cout << "Thoi gian ve (gio phut): ";
						cin >> thoiGian.gioVe>>thoiGian.phutVe;
						nhanVien.DS_ThoiGianLamViec.push_back(thoiGian);
						cout << "Nhap tiep (y/n)? ";
						cin >> ch;
						if (ch == 'n') break;
					}
				}
				Node_NhanVien *nodeNhanVien = new Node_NhanVien;
				nodeNhanVien->nhanVien = nhanVien;
				nodeNhanVien->next = NULL;
				Insert(ds_DonVi, nodeNhanVien);
				break;
			}
			case 6: {
				break;
			}
			case 7: {
				break;
			}
		}
	} while (Lua_Chon != 7);
	input.close();
	system("pause");
	return 0;
}
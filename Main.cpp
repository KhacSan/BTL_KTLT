#include<vector>
#include<fstream>
#include<string>
#include<iomanip>
#include<cstdlib>
#include<time.h>
#include<regex>
#include<iostream>
using namespace std;
#define GIO_DEN 8
#define PHUT_DEN 30
#define GIO_VE 16
#define PHUT_VE 30

typedef struct thoiGian {
	string ngayThangNam;
	int gioDen;
	int phutDen;
	int gioVe;
	int phutVe;
}ThoiGian;

typedef struct nhanvien {
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

typedef struct node_NhanVien {
	NhanVien nhanVien;
	node_NhanVien *next;
}Node_NhanVien;

typedef struct donVi {
	string tenDonVi;
	Node_NhanVien *canBo;
	Node_NhanVien *nhanVien;
	struct donVi *next;
	int soNhanVien;  //chi tinh so nhan vien khong tinh chu tich, pho chu tich...
}DonVi;
typedef struct thoiGianLamViec
{
	string thang;
	int gioLam = 0;
	thoiGianLamViec *next;
}ThangLamViec;

// chuyen string sang chu thuong va tra ve chuoi do
string STRLWR(string str)
{
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
		{
			str[i] = str[i] + 32;
		}
	}
	return str;
}

// so sánh 2 ki tu dau tien cua 2 chuoi chuỗi, tra ve 0 neu 2 chuoi bang nhau, 1 neu str1 > str2, -1 neu str1 < str2.
int nemcmp(string str1, string str2) {
	str1 = STRLWR(str1);
	str2 = STRLWR(str2);
	for (int i = 0; i < 2; i++)
	{
		if (str1[i] > str2[i])
			return 1;
		else if (str1[i] < str2[i])
			return -1;
	}
	return 0;
}
//đọc thời gian làm việc của 1 nhân viên, den khi gap ma nhan vien tiep theo thi dung lai
void DocThoiGianLamViec(ifstream &input, ThoiGian &ThoiGianLamViec) {
	getline(input, ThoiGianLamViec.ngayThangNam, ',');
	input >> ThoiGianLamViec.gioDen;
	input.seekg(1, input.cur); //dich con tro chi vi 1 byte so voi vi tri hien tai
	input >> ThoiGianLamViec.phutDen;
	input.seekg(1, input.cur);
	input >> ThoiGianLamViec.gioVe;
	input.seekg(1, input.cur);
	input >> ThoiGianLamViec.phutVe;
}

//đọc thông tin 1 nhân viên từ file
void DocThongTinMotNhanVien(ifstream &input, NhanVien &nhanvien) {
	int n = 0, count = 0, vitri;
	getline(input, nhanvien.maNhanVien);
	vitri = input.tellg();
	getline(input, nhanvien.ho);
	do
	{
		if (nhanvien.ho != "") break; 
		vitri = input.tellg();
		getline(input, nhanvien.ho);
	} while (true);
	if (nemcmp(nhanvien.ho, "NV") == 0) { // kiem tra xem neu dong moi doc vao la ma nhan vien cua nhan vien tiep theo
		nhanvien.ho = "";                 // thi dung lai va set lai vi tri con tro ve truoc dong do
		input.seekg(vitri, ios::beg);
		return;
	}
	vitri = input.tellg();
	getline(input, nhanvien.ten);
	do
	{
		if (nhanvien.ten != "") break;
		vitri = input.tellg();
		getline(input, nhanvien.ten);
	} while (true);
	if (nemcmp(nhanvien.ten, "NV") == 0) {
		nhanvien.ten = "";
		input.seekg(vitri, ios::beg);
		return;
	}
	vitri = input.tellg();
	getline(input, nhanvien.donVi);
	do
	{
		if (nhanvien.donVi != "") break;
		vitri = input.tellg();
		getline(input, nhanvien.donVi);
	} while (true);
	if (nemcmp(nhanvien.donVi, "NV") == 0) {
		nhanvien.donVi = "";
		input.seekg(vitri, ios::beg);
		return;
	}
	vitri = input.tellg();
	getline(input, nhanvien.chucVu);
	do
	{
		if (nhanvien.chucVu != "") break;
		vitri = input.tellg();
		getline(input, nhanvien.chucVu);
	} while (true);
	if (nemcmp(nhanvien.chucVu, "NV") == 0) {
		nhanvien.chucVu = "";
		input.seekg(vitri, ios::beg);
		return;
	}
	vitri = input.tellg();
	getline(input, nhanvien.ngaySinh);
	do
	{
		if (nhanvien.ngaySinh != "") break;
		vitri = input.tellg();
		getline(input, nhanvien.ngaySinh);
	} while (true);
	if (nemcmp(nhanvien.ngaySinh, "NV") == 0) {
		nhanvien.ngaySinh = "";
		input.seekg(vitri, ios::beg);
		return;
	}
	vitri = input.tellg();
	getline(input, nhanvien.queQuan);
	do
	{
		if (nhanvien.queQuan != "") break;
		vitri = input.tellg();
		getline(input, nhanvien.queQuan);
	} while (true);
	if (nemcmp(nhanvien.queQuan, "NV") == 0) {
		nhanvien.queQuan = "";
		input.seekg(vitri, ios::beg);
		return;
	}
	vitri = input.tellg();
	getline(input, nhanvien.diaChi);
	do
	{
		if (nhanvien.diaChi != "") break;
		vitri = input.tellg();
		getline(input, nhanvien.diaChi);
	} while (true);
	if (nemcmp(nhanvien.diaChi, "NV") == 0) {
		nhanvien.diaChi = "";
		input.seekg(vitri, ios::beg);
		return;
	}
	vitri = input.tellg();
	getline(input, nhanvien.email);
	do
	{
		if (nhanvien.email != "") break;
		vitri = input.tellg();
		getline(input, nhanvien.email);
	} while (true);
	if (nemcmp(nhanvien.email, "NV") == 0) {
		nhanvien.email = "";
		input.seekg(vitri, ios::beg);
		return;
	}
	vitri = input.tellg();
	getline(input, nhanvien.sdt);
	do
	{
		if (nhanvien.sdt != "") break;
		vitri = input.tellg();
		getline(input, nhanvien.sdt);
	} while (true);
	if (nemcmp(nhanvien.sdt, "NV") == 0) {
		nhanvien.sdt = "";
		input.seekg(vitri, ios::beg);
		return;
	}
	vitri = input.tellg();
	getline(input, nhanvien.ngayBatDauLamViec);
	do
	{
		if (nhanvien.ngayBatDauLamViec != "") break;
		vitri = input.tellg();
		getline(input, nhanvien.ngayBatDauLamViec);
	} while (true);
	if (nemcmp(nhanvien.ngayBatDauLamViec, "NV") == 0) {
		nhanvien.ngayBatDauLamViec = "";
		input.seekg(vitri, ios::beg);
		return;
	}
	ThoiGian  thoiGianLamViec;
	string Temp;
	while (true)
	{
		if (input.eof()) break;
		vitri = input.tellg();
		getline(input, Temp);
		if (nemcmp(Temp, "NV") == 0) {
			input.seekg(vitri, ios::beg);
			break;
		}
		if ((Temp != "")){
			input.seekg(vitri, ios::beg);
			DocThoiGianLamViec(input, thoiGianLamViec);
			nhanvien.DS_ThoiGianLamViec.push_back(thoiGianLamViec);
		}
	}
}
//xuất thời gian theo định dạng dd/mm/yyy,hh/mm,hh/mm
void xuatThoiGian(ThoiGian thoiGian) {
	cout << left << "Ngay : " << thoiGian.ngayThangNam << "," << setw(2) << right << setfill('0') << thoiGian.gioDen
		<< setfill(' ') << ":" << setw(2) << right << setfill('0') << thoiGian.phutDen << setfill(' ')
		<< "," << setw(2) << right << setfill('0') << thoiGian.gioVe << setfill(' ') << ":"
		<< setw(2) << right << setfill('0') << thoiGian.phutVe << setfill(' ') << endl;
}
//xuất thông tin cơ bản về một nhân viên gồm: họ,tên,ngày sinh,quê quán,địa chỉ,đơn vị, chức vụ
void xuatThongTinCoBanMotNhanVien(NhanVien nhanvien) {
	cout << left << setw(15) << nhanvien.ho << setw(10) << nhanvien.ten << setw(8) << nhanvien.maNhanVien << setw(12)
		<< nhanvien.ngaySinh << setw(15) << nhanvien.queQuan << setw(25) << nhanvien.diaChi
		<< setw(20) << nhanvien.donVi << setw(10) << nhanvien.chucVu << endl;
}

// tao mot danh sach lien ket don vong rong de luu tru cac don vi
void create_LinkList_DonVi(DonVi *&ds_DonVi) {
	ds_DonVi = NULL;
}

//tao mot don vi moi co ten tuong ung voi ten don vi cua nhan vien them vao
void creat_DonVi(DonVi *&donVi, Node_NhanVien *nodeNhanVien) {
	donVi->tenDonVi = nodeNhanVien->nhanVien.donVi;
	if (_stricmp(((nodeNhanVien->nhanVien).chucVu).c_str(), "Nhan vien") == 0) { //c_str chuyen ve mang char
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

// thêm 1 Node_NhanVien mới vao danh sach cong ty
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

// đọc thông tin từ file NhanVien.txt tra ve -1 nếu đọc không thành công ngược lại trả về 0
int DocFile(ifstream &input, DonVi *&ds_DonVi) {
	input.seekg(0, ios::end);    // dich chuyen con tro den cuoi file
	if (!input.tellg()) {      // kiem tra file co rong hay khong
		return -1;
	}
	else
	{
		input.seekg(0, ios::beg);      // tra lai con tro ve dau file
		while (input.eof() == false)
		{
			NhanVien nhanvien;
			cin.sync();
			DocThongTinMotNhanVien(input, nhanvien);
			Node_NhanVien *nodeNhanVien = new Node_NhanVien;
			nodeNhanVien->nhanVien = nhanvien;
			nodeNhanVien->next = NULL;
			Insert(ds_DonVi, nodeNhanVien);
		}
		return 0;
	}
}

// xuat toàn bộ thông tin đọc được từ file (Thong tin cong ty BKCorporation)
void Output(DonVi *ds_DonVi) {
	if (ds_DonVi == NULL) {
		cout << "Khong co thong tin de hien thi" << endl;
		return;
	}
	else
	{
		DonVi *pDonVi = ds_DonVi;
		while (true)
		{
			cout << pDonVi->tenDonVi << ": " << endl;
			cout << left << setw(15) << "Ho" << setw(10) << "Ten" << setw(8) << "Ma NV" << setw(12) << "Ngay Sinh"
				<< setw(15) << "Que Quan" << setw(25) << "Dia Chi" << setw(20)
				<< "Don Vi" << setw(10) << "Chuc Vu" << endl;
			Node_NhanVien *pCanBo = pDonVi->canBo;
			while (true)
			{
				if (pCanBo == NULL) break;
				xuatThongTinCoBanMotNhanVien(pCanBo->nhanVien);
				pCanBo = pCanBo->next;
			}
			Node_NhanVien *pNhanVien = pDonVi->nhanVien;
			while (true)
			{
				if (pNhanVien == NULL) break;
				xuatThongTinCoBanMotNhanVien(pNhanVien->nhanVien);
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
//tìm kiếm một đơn vị trả về đơn vị đó nếu tìm thấy ngược lại không có trả về 0
DonVi *timKiemMotDonVi(DonVi *ds_DonVi, string tenDonVi) {
	DonVi *pDonVi = ds_DonVi;
	while (true)
	{
		if (_stricmp(pDonVi->tenDonVi.c_str(), tenDonVi.c_str()) == 0)
			return pDonVi;
		if (pDonVi->next == ds_DonVi) break;
		pDonVi = pDonVi->next;
	}
	return NULL;
}
// xuất thông tin cơ bản về một công ty gồm thông tin cơ bản về các nhân viên đó trong công ty
void xuatThongTinCoBanVeMotDonVi(DonVi *ds_DonVi, string tenDonVi)
{
	if (ds_DonVi == NULL) {
		return;
	}
	else
	{
		DonVi *pDonVi = timKiemMotDonVi(ds_DonVi, tenDonVi);
		if (pDonVi == NULL) {
			cout << "\nKhong co don vi nay trong danh sach!" << endl;
			return;
		}
		else
		{
			Node_NhanVien *pCanBo = pDonVi->canBo;
			if (pCanBo == NULL) {
				cout << "\nKhong co thong tin can bo!\n" << endl;
			}
			else
			{
				cout << "Thong tin can bo: " << endl;
				cout << left << setw(15) << "Ho" << setw(10) << "Ten" << setw(8) << "Ma NV" << setw(12) << "Ngay Sinh"
					<< setw(15) << "Que Quan" << setw(25) << "Dia Chi" << setw(20) << "Don Vi" << setw(10) << "Chuc Vu" << endl;
				while (true)
				{
					if (pCanBo == NULL) {
						break;
					}
					else
					{
						xuatThongTinCoBanMotNhanVien(pCanBo->nhanVien);
						pCanBo = pCanBo->next;
					}
				}
			}
			Node_NhanVien *pNhanVien = pDonVi->nhanVien;
			if (pNhanVien == NULL) {
				cout << "\nKhong co thong tin nhan vien!" << endl;
			}
			else
			{
				cout << "Thong tin nhan vien: " << endl;
				cout << left << setw(15) << "Ho" << setw(10) << "Ten" << setw(8) << "Ma NV" << setw(12) << "Ngay Sinh"
					<< setw(15) << "Que Quan" << setw(25) << "Dia Chi" << setw(20) << "Don Vi" << setw(10) << "Chuc Vu" << endl;
				while (true)
				{
					if (pNhanVien == NULL) {
						break;
					}
					else
					{
						xuatThongTinCoBanMotNhanVien(pNhanVien->nhanVien);
						pNhanVien = pNhanVien->next;
					}
				}
			}
		}
		return;
	}
}
//xuất thông tin cơ bản về công ty BKCorporation gồm thông tin cơ bản cuả cán bộ trong từng công ty
void XuatThongTinCoBanVeCongTy(DonVi *ds_DonVi) {
	if (ds_DonVi == NULL) {
		cout << "Khong co thong tin de hien thi" << endl;
		return;
	}
	else
	{
		DonVi *p = ds_DonVi;
		int TongSoNhanVien = 0;
		while (true)
		{
			TongSoNhanVien += p->soNhanVien;
			Node_NhanVien *pCanBo = p->canBo;
			cout << "\n" << p->tenDonVi << " : " << endl;
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
		cout << "\nTong So Nhan Vien = " << TongSoNhanVien << endl;
	}
}
//tim kiem gan dung theo thong tin nguoi dung nhap vao tra ve null neu danh sach nhan vien rong, nguoc lai tra ve danh sach tim kiem
////SEARCHING
void xuatThongTinMotNhanVien(NhanVien nhanvien)
{
	cout << left << setw(5) << nhanvien.maNhanVien << setw(12) << nhanvien.ho << setw(7) << nhanvien.ten << setw(12)
		<< nhanvien.chucVu << setw(11) << nhanvien.ngaySinh << setw(8) << nhanvien.queQuan
		<< setw(20) << nhanvien.diaChi << setw(24) << nhanvien.email << setw(12) << nhanvien.sdt << endl;
}
Node_NhanVien *SaoChepNodeNhanVien(Node_NhanVien *pNhanVien)
{
	Node_NhanVien *pNode = new Node_NhanVien();
	pNode->nhanVien.ho = pNhanVien->nhanVien.ho;
	pNode->nhanVien.ten = pNhanVien->nhanVien.ten;
	pNode->nhanVien.diaChi = pNhanVien->nhanVien.diaChi;
	pNode->nhanVien.queQuan = pNhanVien->nhanVien.queQuan;
	pNode->nhanVien.sdt = pNhanVien->nhanVien.sdt;
	pNode->nhanVien.ngaySinh = pNhanVien->nhanVien.ngaySinh;
	pNode->nhanVien.donVi = pNhanVien->nhanVien.donVi;
	pNode->nhanVien.ngayBatDauLamViec = pNhanVien->nhanVien.ngayBatDauLamViec;
	pNode->nhanVien.email = pNhanVien->nhanVien.email;
	pNode->nhanVien.DS_ThoiGianLamViec = pNhanVien->nhanVien.DS_ThoiGianLamViec;
	pNode->nhanVien.maNhanVien = pNhanVien->nhanVien.maNhanVien;
	pNode->nhanVien.chucVu = pNhanVien->nhanVien.chucVu;
	pNode->next = NULL;
	return pNode;
}
//Xử lý xâu tim kiếm, chia thành các khóa tìm kiếm đơn
void XuLyXauTK(vector<string> &vet, string strSearch)
{
	string temp = "";
	for (int i = 0; i < strSearch.length(); ++i)
	{
		if (strSearch[i] == ' ')
		{
			if (temp != "")
			{
				vet.push_back(temp);
				temp = "";
				continue;
			}
			else continue;
		}
		else
		{
			temp = temp + strSearch[i];
			continue;
		}
	}
	if (temp != "")
		vet.push_back(temp);
}
//Tìm kiếm trong danh sách với khóa đầu tiên của chuỗi tìm kiếm, đếm lại số kết quả tìm được và ghi danh sách kết quả này vào ds_TimKiem
void SearchFirst(DonVi *ds_DonVi, string strSearch, Node_NhanVien *&ds_TimKiem, int &countResult)
{
	DonVi *pDonVi = ds_DonVi;
	while (true)
	{
		Node_NhanVien *pCanBo = pDonVi->canBo;
		while (true)
		{
			if (pCanBo == NULL) break;
			if (strstr((STRLWR(pCanBo->nhanVien.ten)).c_str(), STRLWR(strSearch).c_str()) != NULL
				|| strstr((STRLWR(pCanBo->nhanVien.ho)).c_str(), STRLWR(strSearch).c_str()) != NULL
				|| strstr((STRLWR(pCanBo->nhanVien.email)).c_str(), STRLWR(strSearch).c_str()) != NULL
				|| strstr((STRLWR(pCanBo->nhanVien.ngayBatDauLamViec)).c_str(), STRLWR(strSearch).c_str()) != NULL
				|| _stricmp((pCanBo->nhanVien.maNhanVien).c_str(), strSearch.c_str()) == 0
				|| strstr((STRLWR(pCanBo->nhanVien.ngaySinh)).c_str(), STRLWR(strSearch).c_str()) != NULL
				|| strstr((STRLWR(pCanBo->nhanVien.chucVu)).c_str(), (STRLWR(strSearch)).c_str()) != NULL
				|| strstr((STRLWR(pCanBo->nhanVien.queQuan)).c_str(), (STRLWR(strSearch)).c_str()) != NULL
				|| strstr((STRLWR(pCanBo->nhanVien.diaChi)).c_str(), (STRLWR(strSearch)).c_str()) != NULL
				|| strstr(pCanBo->nhanVien.sdt.c_str(), (STRLWR(strSearch)).c_str()) != NULL)
			{
				countResult++;
				Node_NhanVien *pSaoChep = SaoChepNodeNhanVien(pCanBo);
				if (ds_TimKiem == NULL)
				{
					ds_TimKiem = pSaoChep;
				}
				else
				{
					Node_NhanVien *pNode = ds_TimKiem;
					ds_TimKiem = pSaoChep;
					pSaoChep->next = pNode;
				}
			}
			pCanBo = pCanBo->next;
		}
		Node_NhanVien *pNhanVien = pDonVi->nhanVien;
		while (true)
		{
			if (pNhanVien == NULL) break;
			if (strstr((STRLWR(pNhanVien->nhanVien.ten)).c_str(), (STRLWR(strSearch)).c_str()) != NULL
				|| strstr((pNhanVien->nhanVien.ho).c_str(), (STRLWR(strSearch)).c_str()) != NULL
				|| strstr((STRLWR(pNhanVien->nhanVien.email)).c_str(), (STRLWR(strSearch)).c_str()) != NULL
				|| strstr((STRLWR(pNhanVien->nhanVien.ngayBatDauLamViec)).c_str(), (STRLWR(strSearch)).c_str()) != NULL
				|| _stricmp((pNhanVien->nhanVien.maNhanVien).c_str(), strSearch.c_str()) == 0
				|| strstr((STRLWR(pNhanVien->nhanVien.ngaySinh)).c_str(), STRLWR(strSearch).c_str()) != NULL
				|| strstr((STRLWR(pNhanVien->nhanVien.queQuan)).c_str(), STRLWR(strSearch).c_str()) != NULL
				|| strstr((STRLWR(pNhanVien->nhanVien.diaChi)).c_str(), STRLWR(strSearch).c_str()) != NULL
				|| strstr((STRLWR(pNhanVien->nhanVien.chucVu)).c_str(), (STRLWR(strSearch)).c_str()) != NULL
				|| strstr(pNhanVien->nhanVien.sdt.c_str(), (STRLWR(strSearch)).c_str()) != NULL)
			{
				countResult++;
				Node_NhanVien *pSaoChep = SaoChepNodeNhanVien(pNhanVien);
				if (ds_TimKiem == NULL)
				{
					ds_TimKiem = pSaoChep;
				}
				else
				{
					Node_NhanVien *pNode = ds_TimKiem;
					ds_TimKiem = pSaoChep;
					pSaoChep->next = pNode;
				}
			}
			pNhanVien = pNhanVien->next;
		}
		if (pDonVi->next == ds_DonVi)
		{
			break;
		}
		pDonVi = pDonVi->next;
	}
}
//Tìm kiếm với các khóa tìm kiếm sau, ghi lại số lần tìm thấy của các khóa sau của từng phần tử của ds_TimKiem
void SearchAfter(Node_NhanVien *ds_TimKiem, string strSearch, vector<int> &Check, int countResult)
{
	Node_NhanVien *pNhanVien = ds_TimKiem;
	for (int countSearch = 0; countSearch < countResult; countSearch++)
	{
		if (pNhanVien == NULL) break;
		if (strstr((STRLWR(pNhanVien->nhanVien.ten)).c_str(), STRLWR(strSearch).c_str()) != NULL
			|| strstr((STRLWR(pNhanVien->nhanVien.ho)).c_str(), STRLWR(strSearch).c_str()) != NULL
			|| strstr((STRLWR(pNhanVien->nhanVien.email)).c_str(), STRLWR(strSearch).c_str()) != NULL
			|| strstr((STRLWR(pNhanVien->nhanVien.ngayBatDauLamViec)).c_str(), STRLWR(strSearch).c_str()) != NULL
			|| _stricmp((pNhanVien->nhanVien.maNhanVien).c_str(), strSearch.c_str()) == 0
			|| strstr((STRLWR(pNhanVien->nhanVien.ngaySinh)).c_str(), STRLWR(strSearch).c_str()) != NULL
			|| strstr((STRLWR(pNhanVien->nhanVien.chucVu)).c_str(), (STRLWR(strSearch)).c_str()) != NULL
			|| strstr((STRLWR(pNhanVien->nhanVien.queQuan)).c_str(), (STRLWR(strSearch)).c_str()) != NULL
			|| strstr((STRLWR(pNhanVien->nhanVien.diaChi)).c_str(), (STRLWR(strSearch)).c_str()) != NULL
			|| strstr(pNhanVien->nhanVien.sdt.c_str(), (STRLWR(strSearch)).c_str()) != NULL)
		{
			Check[countSearch]++;
		}
		pNhanVien = pNhanVien->next;
	}
}
//Tìm kiếm với tất cả các khóa và in ra danh sách kết quả
void Search(DonVi *ds_DonVi, vector<string> vet)
{
	if (ds_DonVi == NULL)
	{
		return;
	}
	else
	{
		Node_NhanVien *ds_TimKiem = NULL;
		int countResult = 0;
		SearchFirst(ds_DonVi, vet[0], ds_TimKiem, countResult);
		vector<int> Check;
		for (int i = 0; i < countResult; ++i)
			Check.push_back(0);
		for (int i = 1; i< vet.size(); i++)
		{
			string strSearch = vet[i];
			SearchAfter(ds_TimKiem, strSearch, Check, countResult);
		}
		int sumOfResult = 0;
		if (ds_TimKiem == NULL)
		{
			cout << "Khong tim thay thong tin ban vua nhap" << endl;
			return;
		}
		else
		{
			int bingo = vet.size() - 1;
			int pCount;
			Node_NhanVien *pResult = ds_TimKiem;
			for (pCount = 0; pCount < countResult; pCount++)
			{
				if (Check[pCount] == bingo)
					sumOfResult++;
			}
			if (sumOfResult == 0)
				cout << "Khong tim thay thong tin ban vua nhap." << endl;
			else
			{
				cout << left << setw(5) << "MaNV" << setw(12) << "Ho" << setw(7) << "Ten" << setw(12)
					<< "Chuc Vu" << setw(11) << "Ngay Sinh" << setw(8) << "Que Quan"
					<< setw(20) << "Dia Chi" << setw(24) << "Email" << setw(12) << "So DT" << endl;
				for (pCount = 0; pCount < countResult; pCount++)
				{
					if (Check[pCount] == bingo)
					{
						xuatThongTinMotNhanVien(pResult->nhanVien);
					}
					pResult = pResult->next;
				}
				cout << endl;
				cout << "Tong so ket qua tim duoc:" << sumOfResult << endl;
			}
		}
	}
}
//tim 1 nhan vien theo ma nhan vien tra ve null neu khong tim thay, nguoc lai tra ve Node_NhanVien tuong ung
Node_NhanVien *TimKiemTheoMaNhanVien(DonVi *ds_DonVi, string maNhanVien) {
	if (ds_DonVi == NULL) {
		return NULL;
	}
	else
	{
		DonVi *pDonVi = ds_DonVi;
		while (true)
		{
			Node_NhanVien *pCanBo = pDonVi->canBo;
			while (true)
			{
				if (pCanBo == NULL) break;
				if (_stricmp((pCanBo->nhanVien.maNhanVien).c_str(), maNhanVien.c_str()) == 0)
				{
					return pCanBo;
				}
				pCanBo = pCanBo->next;
			}
			Node_NhanVien *pNhanVien = pDonVi->nhanVien;
			while (true)
			{
				if (pNhanVien == NULL) break;
				if (_stricmp((pNhanVien->nhanVien.maNhanVien).c_str(), maNhanVien.c_str()) == 0)
				{
					return pNhanVien;
				}
				pNhanVien = pNhanVien->next;
			}
			if (pDonVi->next == ds_DonVi)
			{
				break;
			}
			pDonVi = pDonVi->next;
		}
	}
	return NULL;
}

//kiem tra 1 chuoi co la so dien thoai khong
bool ckeck_SDT(string SDT) {
	regex pattern("(\\+84|0)\\d{9,10}");
	return regex_match(SDT, pattern);
}
//kiem tra 1 chuoi co dung dinh dang ngay thang nam (dd/mm/yyyy) khong? neu dung tra ve true, nguoc lai tra ve false
bool check_NgayThangNam(string ngayThangNam) {
	regex pattern("([1-9]|0[1-9]|(1|2)[0-9]|3[0-1])/([1-9]|0[1-9]|1[0-2])/(19|20)[0-9]{2}");
	return regex_match(ngayThangNam, pattern);
}
//kiem tra dinh dang email
bool checkemail(string email)
{
	regex pattern("[a-zA-Z0-9_\.]+@[a-zA-Z]+\.[a-zA-Z]+(\.[a-zA-Z]+)*");// Hàm regex_match() dùng để kiểm tra TOÀN BỘ chuỗi
	return regex_match(email, pattern);                                 // Hàm regex_search() dùng để kiểm tra CHUỖI CON trong chuỗi
}
bool checkChucVu(string chucVu) {
	regex pattern("(nhan vien|((pho giam|giam)+ doc))+");
	return regex_match(chucVu, pattern);
}
bool checkHo(string ho)
{
	regex pattern("^[A-Za-z]+");// 
	return regex_match(ho, pattern);
}
bool checkTen(string ten)
{
	regex pattern("^[A-Za-z]+");// 
	return regex_match(ten, pattern);
}
void ThemMotNhanVien(DonVi *&ds_DonVi) {
	NhanVien nhanVien;
	cout << "Nhap Thong tin nhan vien can them: " << endl;
	cout << "Ho: ";
	cin.ignore();//xoa bo bo dem
	getline(cin, nhanVien.ho);
	cout << "Ten: ";
	cin.sync();   //xoa bo dem
	getline(cin, nhanVien.ten);
	cout << "Ma nhan vien: ";
	string maNhanVien;
	cin.sync();
	getline(cin, maNhanVien);
	do
	{
		if (TimKiemTheoMaNhanVien(ds_DonVi, maNhanVien) == NULL) break;
		else
		{
			cout << "Ma nhan vien ban vua nhap da ton tai vui long nhan lai ma nhan vien: ";
			getline(cin, maNhanVien);
		}
	} while (true);
	nhanVien.maNhanVien = maNhanVien;
	cout << "Don vi: ";
	cin.sync();
	getline(cin, nhanVien.donVi);
	cout << "Chuc vu: ";
	cin.sync();
	getline(cin, nhanVien.chucVu);
	cout << "Ngay thang nam sinh (dd/mm/yyyy): ";
	cin.sync();
	getline(cin, nhanVien.ngaySinh);
	do
	{
		if (check_NgayThangNam(nhanVien.ngaySinh)) break;
		cout << "Ngay sinh khong hop loi moi ban nhap lai (dd/mm/yyyy): ";
		cin.sync();
		getline(cin, nhanVien.ngaySinh);
	} while (true);
	cout << "Que quan: ";
	cin.sync();
	getline(cin, nhanVien.queQuan);
	cout << "Dia chi: ";
	cin.sync();
	getline(cin, nhanVien.diaChi);
	cout << "Email: ";
	cin.sync();
	getline(cin, nhanVien.email);
	do
	{
		if (checkemail(nhanVien.email)) break;
		cout << "Email khong hop le vui long nhap lai: ";
		cin.sync();
		getline(cin, nhanVien.email);
	} while (true);
	cout << "So dien thoai: ";
	cin.sync();
	getline(cin, nhanVien.sdt);
	do
	{
		if (ckeck_SDT(nhanVien.sdt)) break;
		cout << "So dien thoai ban vua nhap khong dung moi ban nhap lai: ";
		cin.sync();
		getline(cin, nhanVien.sdt);
	} while (true);
	cout << "Ngay bat dau lam viec (dd/mm/yyy): ";
	cin.sync();
	getline(cin, nhanVien.ngayBatDauLamViec);
	do
	{
		if (check_NgayThangNam(nhanVien.ngayBatDauLamViec)) break;
		cout << "Ngay thang nam khong hop loi moi ban nhap lai (dd/mm/yyyy): ";
		cin.sync();
		getline(cin, nhanVien.ngayBatDauLamViec);
	} while (true);
	char ch;
	cout << "Nhap thoi gian lam viec (y/n)?";
	cin >> ch;
	if (ch == 'y' || ch == 'Y') {
		while (true)
		{
			ThoiGian thoiGian;
			cout << "Ngay lam viec: ";
			cin.ignore();
			getline(cin, thoiGian.ngayThangNam);
			cout << "Thoi gian bat dau: " << endl;
			cout << "Thoi gian den (gio phut): ";
			cin >> thoiGian.gioDen >> thoiGian.phutDen;
			cout << "Thoi gian ve (gio phut): ";
			cin >> thoiGian.gioVe >> thoiGian.phutVe;
			nhanVien.DS_ThoiGianLamViec.push_back(thoiGian);
			cout << "Nhap tiep (y/n)? ";
			cin >> ch;
			if (ch == 'n') break;
		}
	}
	clock_t start = clock();
	Node_NhanVien *nodeNhanVien = new Node_NhanVien;
	nodeNhanVien->nhanVien = nhanVien;
	nodeNhanVien->next = NULL;
	Insert(ds_DonVi, nodeNhanVien);
	clock_t finish = clock();
	cout << "\nThoi gian thuc hien: " << (double)(finish - start) / CLOCKS_PER_SEC << "s" << endl;
}

//tinh thoi gian lam viec cua nhan vien theo khung thoi gian 8:30->16:30, 
//tra ve thoi gian lam viec tuong ung cua nhan vien lam tron theo gio, neu nhan vien lam du tra ve 0,
//thieu tra ve gia tri am, nguoc lai neu lam them tra ve gia tri duong tuong ung voi so gio thieu,thua
int TinhThoiGianMotNgay(ThoiGian thoiGian)
{
		int TongThoiGian = 0;
			if (thoiGian.gioDen > GIO_DEN) {
				TongThoiGian -= ((thoiGian.gioDen - 1 - GIO_DEN) * 60 + (60 - PHUT_DEN) +  thoiGian.phutDen);
			}
			else
			{
				if (thoiGian.gioDen < GIO_DEN) {
					TongThoiGian += (GIO_DEN - 1 - thoiGian.gioDen) * 60 + (60 - thoiGian.phutDen) + PHUT_DEN;
				}
				else
				{
					if (thoiGian.phutDen >= PHUT_DEN) TongThoiGian -= (thoiGian.phutDen - PHUT_DEN);
					else TongThoiGian += PHUT_DEN - thoiGian.phutDen;
				}
			}
			if (thoiGian.gioVe < GIO_VE) {
				TongThoiGian -= ((GIO_VE - 1 - thoiGian.gioVe) * 60 + (60 - thoiGian.phutVe) + PHUT_VE);
			}
			else
			{
				if (thoiGian.gioVe > GIO_VE) {
					TongThoiGian += (thoiGian.gioVe - 1 - GIO_VE) * 60 + (60 - PHUT_VE) + thoiGian.phutVe;
				}
				else
				{
					if (thoiGian.phutVe <= PHUT_VE) TongThoiGian -= (PHUT_VE - thoiGian.phutVe);
					else
					{
						TongThoiGian += thoiGian.phutVe - PHUT_VE;
					}
				}
			}
			return TongThoiGian;
}
//chuan hoa ngay thang nam ve dang dd/mm/yyyy
string chuanHoa(string str) {
	string temp = "         ";
	if (str.length() == 10)
		return str;
	else {
		if (str[2] == '/') { // truong hop dd/m/yyyy
			temp[0] = str[0];
			temp[1] = str[1];
			temp[2] = str[2];
			temp[3] = '0';
			for (int i = 3; i <= 8; i++)
				temp[i + 1] = str[i];
		}
		else if (str[3] == '/') {		//truong hop d/m/yyyy
			temp[0] = '0';
			temp[1] = str[0];
			temp[2] = str[1];
			temp[3] = '0';
			temp[4] = str[2];
			for (int i = 4; i <= 8; i++)
				temp[i + 1] = str[i - 1];
		}
		else {							//truong hop d/mm/yyyy
			temp[0] = '0';
			for (int i = 0; i <= 8; i++)
				temp[i + 1] = str[i];
		}
	}
	return temp;
}
string cat(string str) {
	string str1 = chuanHoa(str);
	string temp = "  ";
	temp[0] = str1[3];
	temp[1] = str1[4];
	return temp;
}
ThangLamViec *timKiemMotThang(ThangLamViec *ds_Thang,string thang) {
	ThangLamViec *pThang = ds_Thang;
	while (true)
	{
		if (_stricmp(pThang->thang.c_str(), thang.c_str()) == 0)
		{
			return pThang;
		}
		if (pThang->next == NULL) break;
		pThang = pThang->next;
	}
	return NULL;
}
ThangLamViec *tinhThoiGianLamViec(vector<ThoiGian> ds_ThoiGian) {
	if (ds_ThoiGian.size() == 0)
	{
		return NULL;
	}
	else
	{
		ThangLamViec *ds_Thang = NULL;
		for (int i = 0; i < ds_ThoiGian.size(); i++)
		{
			if (ds_Thang == NULL) {
				ThangLamViec *thoiGian = new ThangLamViec;
				thoiGian->thang = cat(ds_ThoiGian[i].ngayThangNam);
				thoiGian->gioLam += TinhThoiGianMotNgay(ds_ThoiGian[i]);
				thoiGian->next = NULL;
				ds_Thang = thoiGian;
			}
			else
			{
				string thang = cat(ds_ThoiGian[i].ngayThangNam);
				ThangLamViec *pThang = timKiemMotThang(ds_Thang, thang);
				if (pThang == NULL) {
					ThangLamViec *thoiGian = new ThangLamViec;
					thoiGian->thang = thang;
					thoiGian->gioLam += TinhThoiGianMotNgay(ds_ThoiGian[i]);
					thoiGian->next = ds_Thang;
					ds_Thang = thoiGian;
				}
				else
				{
					pThang->gioLam += TinhThoiGianMotNgay(ds_ThoiGian[i]);
				}
			}
		}
		return ds_Thang;
	}
 }

void HienThiTrangThaiLamViec(DonVi *ds_DonVi, string maNhanVien) {
	Node_NhanVien *pNhanVien = TimKiemTheoMaNhanVien(ds_DonVi, maNhanVien);
	if (pNhanVien == NULL) {
		cout << "Khong co nhan vien mang ma nay trong cong ty." << endl;
		return;
	}
	else
	{
		ThangLamViec *ds_Thang = tinhThoiGianLamViec(pNhanVien->nhanVien.DS_ThoiGianLamViec);
		if(ds_Thang== NULL){	
			cout << "Khong co thong tin ngay lam viec cua nhan vien nay" << endl;
			return;
		}
		else
		{
			cout << "\nDanh sach thoi gian lam viec: " << endl;
			for (int i = 0; i < pNhanVien->nhanVien.DS_ThoiGianLamViec.size(); i++) {
				xuatThoiGian(pNhanVien->nhanVien.DS_ThoiGianLamViec[i]);
			}
			cout << endl;
			while (true)
			{
				int TongThoiGian = 0;
				if (ds_Thang->gioLam < 0) {
					if (ds_Thang->gioLam % 60 <= -30) {
						TongThoiGian = (int)ds_Thang->gioLam / 60 - 1;
					}
					else
					{
						TongThoiGian = (int)ds_Thang->gioLam / 60;
					}
				}
				else
				{
					if (ds_Thang->gioLam % 60 >= 30) {
						TongThoiGian = (int)ds_Thang->gioLam / 60 + 1;
					}
					else
					{
						TongThoiGian = (int)ds_Thang->gioLam / 60;
					}
				}
				if (ds_Thang->gioLam < 0) {
					cout << "Thoi gian thieu cua nhan vien "<<maNhanVien<<" trong thang "
						 <<ds_Thang->thang<<" la: " << (0 - TongThoiGian) << " gio" << endl;
				}
				else
				{
					if (ds_Thang->gioLam > 0) {
						cout << "Thoi gian thieu cua nhan vien " << maNhanVien << " trong thang "
							<< ds_Thang->thang << " la: " << TongThoiGian << " gio" << endl;
					}
					else
					{
						cout << "Nhan vien nay lam du thoi gian trong thang " << TongThoiGian << endl;
					}
				}
				if (ds_Thang->next == NULL)
				{
					break;
				}
				ds_Thang = ds_Thang->next;
			}
		}
	}
}
// tim va tra ve nhan vien co ma tuong ung dong thoi luu vet don vi chua nhan vien do trong bang *pDonVi va luu vet node truoc node can tim bang *preNhanVien
Node_NhanVien *TimKiemTheoMaNhanVien(DonVi *ds_DonVi, DonVi *&pDonVi,Node_NhanVien *&preNhanVien, string maNhanVien) {
	if (ds_DonVi == NULL) {
		return NULL;
	}
	else
	{
		pDonVi = ds_DonVi;
		while (true)
		{
			preNhanVien = pDonVi->canBo;
			if (preNhanVien != NULL) {
				if (_stricmp(preNhanVien->nhanVien.maNhanVien.c_str(), maNhanVien.c_str()) == 0) return preNhanVien;
				else
				{
					while (true)
					{
						if (preNhanVien->next == NULL) break;
						if (_stricmp((preNhanVien->next->nhanVien.maNhanVien).c_str(), maNhanVien.c_str()) == 0)
						{
							return preNhanVien->next;
						}
						preNhanVien = preNhanVien->next;
					}
				}
			}
			preNhanVien = pDonVi->nhanVien;
			if (preNhanVien != NULL) {
				if (preNhanVien != NULL && _stricmp(preNhanVien->nhanVien.maNhanVien.c_str(), maNhanVien.c_str()) == 0) return preNhanVien;
				else
				{
					while (true)
					{
						if (preNhanVien->next == NULL) break;
						if (_stricmp((preNhanVien->next->nhanVien.maNhanVien).c_str(), maNhanVien.c_str()) == 0)
						{
							return preNhanVien->next;
						}
						preNhanVien = preNhanVien->next;
					}
				}
			}
			if (pDonVi->next == ds_DonVi) break;
			pDonVi = pDonVi->next;
		}
	}
	return NULL;
}

// cap nhat thong tin 1 nhan vien theo ma nhan vien tra ve -1 neu khong co nhan vien nay trong cong ty, 
//tra ve 0 neu cap nhat thanh cong
int UpdateInfo_NhanVien(DonVi *&ds_DonVi, string maNhanVien) {
	DonVi *pDonVi;
	Node_NhanVien *preNhanVien;
	Node_NhanVien *pNhanVien = TimKiemTheoMaNhanVien(ds_DonVi, pDonVi, preNhanVien, maNhanVien);
	if (pNhanVien == NULL) {
		return -1;
	}
	else {
		int LuaChon;
		do {
			cout << "Chon muc can cap nhat: " << endl;
			cout << "01. Ho" << endl;
			cout << "02. Ten" << endl;
			cout << "03. Ngay sinh" << endl;
			cout << "04. Que quan" << endl;
			cout << "05. Dia chi" << endl;
			cout << "06. SDT" << endl;
			cout << "07. Email" << endl;
			cout << "08. Chuc vu" << endl;
			cout << "09. Don Vi" << endl;
			cout << "10. Ngay bat dau lam viec" << endl;
			cout << "11. Thoat" << endl;
			cout << "Ban chon: ";
			cin >> LuaChon;
			if (cin.fail() || LuaChon < 1 || LuaChon > 11) {
				cin.clear();
				cin.ignore(32767, '\n');
				system("cls");
				cout << "Ban chon sai! vui long thu lai!" << endl;
				return 1;
			}
			clock_t start;
			clock_t end;
			double waitTime = 0;
			double sumTime = 0;
			switch (LuaChon) {
			case 1: {
				string str = "";
				cout << "Nhap ho: ";
				cin.ignore();
				getline(cin, str);
				if (str != "") {
					start = clock();
				}
				pNhanVien->nhanVien.ho = str;
				end = clock();
				sumTime = (end - start);
				while (!checkHo(pNhanVien->nhanVien.ho)) {
					string s = "";
					sumTime = sumTime + waitTime;
					cout << "Ho khong hop le! Vui long nhap lai: ";
					getline(cin, s);
					if (s != "") {
						start = clock();
					}
					cin.sync();
					pNhanVien->nhanVien.ho = s;
					end = clock();
					waitTime = (end - start);
				}
				cout << "Cap nhat thanh cong !" << endl;
				printf("Thoi gian thuc thi: %.6lf", sumTime / CLOCKS_PER_SEC);
				cout << endl;
				break;
			}
			case 2: {
				string str = "";
				cout << "Nhap ten: ";
				cin.ignore();
				getline(cin, str);
				if (str != "") {
					start = clock();
				}
				pNhanVien->nhanVien.ten = str;
				end = clock();
				sumTime = (end - start);
				while (!checkTen(pNhanVien->nhanVien.ten)) {
					string s = "";
					sumTime = sumTime + waitTime;
					cout << "Ten khong hop le! Vui long nhap lai";
					cin.sync();
					getline(cin, s);
					if (s != "") {
						start = clock();
					}
					pNhanVien->nhanVien.ten = s;
					end = clock();
					waitTime = end - start;
				}
				cout << "Cap nhat thanh cong !" << endl;
				printf("Thoi gian thuc thi: %.6lf", sumTime / CLOCKS_PER_SEC);
				cout << endl;
				break;
			}
			case 3: {
				string str = "";
				cout << "Nhap ngay sinh: ";
				cin.ignore();
				getline(cin, str);
				if (str != "") {
					start = clock();
				}
				pNhanVien->nhanVien.ngaySinh = str;
				while (!check_NgayThangNam(pNhanVien->nhanVien.ngaySinh)) {
					string s = "";
					sumTime = sumTime + waitTime;
					cout << "Ngay sinh khong hop le vui long nhap lai: ";
					cin.sync();
					getline(cin, s);
					if (s != "") {
						start = clock();
					}
					pNhanVien->nhanVien.ngaySinh = s;
					end = clock();
					waitTime = end - start;
				}
				cout << "Cap nhat thanh cong !" << endl;
				printf("Thoi gian thuc thi: %.6lf", sumTime / CLOCKS_PER_SEC);
				cout << endl;
				break;
			}
			case 4: {
				string str = "";
				cout << "Nhap que quan: ";
				cin.ignore();
				getline(cin, str);
				if (str != "") {
					start = clock();
				}
				pNhanVien->nhanVien.queQuan = str;
				end = clock();
				sumTime = end - start;
				cout << "Cap nhat thanh cong !" << endl;
				printf("Thoi gian thuc thi: %.6lf", sumTime / CLOCKS_PER_SEC);
				cout << endl;
				break;
			}
			case 5: {
				string str = "";
				cout << "Nhap dia chi: ";
				cin.ignore();
				getline(cin, str);
				if (str != "") {
					start = clock();
				}
				pNhanVien->nhanVien.diaChi = str;
				end = clock();
				sumTime = end - start;
				cout << "Cap nhat thanh cong !" << endl;
				printf("Thoi gian thuc thi: %.6lf", sumTime / CLOCKS_PER_SEC);
				cout << endl;
				break;
			}
			case 6: {
				string str = "";
				cout << "Nhap SDT: ";
				cin.ignore();
				getline(cin, str);
				if (str != "") {
					start = clock();
				}
				pNhanVien->nhanVien.sdt = str;
				end = clock();
				while (!ckeck_SDT(pNhanVien->nhanVien.sdt)) {
					string s = "";
					sumTime = sumTime + waitTime;
					cout << "So dien thoai khong hop le vui long nhap lai: ";
					cin.sync();
					getline(cin, s);
					if (s != "") {
						start = clock();
					}
					pNhanVien->nhanVien.sdt = s;
					end = clock();
					waitTime = end - start;
				}
				cout << "Cap nhat thanh cong !" << endl;
				printf("Thoi gian thuc thi: %.6lf", sumTime / CLOCKS_PER_SEC);
				cout << endl;
				break;
			}
			case 7: {
				string str = "";
				cout << "Nhap Email: ";
				cin.ignore();
				getline(cin, str);
				if (str != "") {
					start = clock();
				}
				pNhanVien->nhanVien.email = str;
				end = clock();
				while (!checkemail(pNhanVien->nhanVien.email)) {
					string s = "";
					sumTime = sumTime + waitTime;
					cout << "Email khong hop le vui long nhap lai: ";
					cin.sync();
					getline(cin, s);
					if (s != "") {
						start = clock();
					}
					pNhanVien->nhanVien.email = s;
					end = clock();
					waitTime = end - start;
				}
				cout << "Cap nhat thanh cong !" << endl;
				printf("Thoi gian thuc thi: %.6lf", sumTime / CLOCKS_PER_SEC);
				cout << endl;
				break;
			}
			case 8: {
				string str = "";
				string chucVu;
				cout << "Nhap chuc vu: ";
				cin.ignore();
				getline(cin, str);
				if (str != "") {
					start = clock();
				}
				chucVu = str;
				end = clock();
				while (!checkChucVu(chucVu)) {
					string s = "";
					sumTime = sumTime + waitTime;
					cout << "Chuc vu khong hop le? Vui long nhap lai: ";
					cin.sync();
					getline(cin, s);
					if (s != "") {
						start = clock();
					}
					chucVu = s;
					end = clock();
					waitTime = end - start;
				}
				sumTime = sumTime + waitTime;
				if (_stricmp(pNhanVien->nhanVien.chucVu.c_str(), "nhan vien") != 0) {
					start = clock();
					if (_stricmp(chucVu.c_str(), "nhan vien") == 0) {
						pNhanVien->nhanVien.chucVu = chucVu;
						if (_stricmp(preNhanVien->nhanVien.maNhanVien.c_str(), maNhanVien.c_str()) == 0) {
							Node_NhanVien *pTemp = preNhanVien;
							pDonVi->canBo = pDonVi->canBo->next;
							Node_NhanVien *pNV = pDonVi->nhanVien;
							pDonVi->nhanVien = pTemp;
							pTemp->next = pNV;
						}
						else {
							Node_NhanVien *pTemp = preNhanVien->next;
							preNhanVien->next = pTemp->next;
							Node_NhanVien *pNV = pDonVi->nhanVien;
							pDonVi->nhanVien = pTemp;
							pTemp->next = pNV;
						}
						pDonVi->soNhanVien++;
						end = clock();
						waitTime = end - start;
					}
				}
				else {
					start = clock();
					if (_stricmp(chucVu.c_str(), "nhan vien") != 0) {
						pNhanVien->nhanVien.chucVu = chucVu;
						if (_stricmp(preNhanVien->nhanVien.maNhanVien.c_str(), maNhanVien.c_str()) == 0) {
							Node_NhanVien *pTemp = preNhanVien;
							pDonVi->nhanVien = pDonVi->nhanVien->next;
							Node_NhanVien *pCB = pDonVi->canBo;
							pDonVi->canBo = pTemp;
							pTemp->next = pCB;
						}
						else {
							Node_NhanVien *pTemp = preNhanVien->next;
							preNhanVien->next = pTemp->next;
							Node_NhanVien *pCB = pDonVi->canBo;
							pDonVi->canBo = pTemp;
							pTemp->next = pCB;
						}
						pDonVi->soNhanVien--;
						end = clock();
						waitTime = end - start;
					}
				}
				sumTime = sumTime + waitTime;
				cout << "Cap nhat thanh cong !" << endl;
				printf("Thoi gian thuc thi: %.6lf", sumTime / CLOCKS_PER_SEC);
				cout << endl;
				break;
			}
			case 9: {
				DonVi *pDanhSachDonVi = ds_DonVi;
				int n = 1;
				cout << "Danh sach cac don vi: " << endl;
				while (true) {
					cout << n << ". " << pDanhSachDonVi->tenDonVi << endl;
					if (pDanhSachDonVi->next == ds_DonVi) break;
					n++;
					pDanhSachDonVi = pDanhSachDonVi->next;
				}
				string donVi;
				cout << "Nhap Ten Don Vi: ";
				cin.ignore();
				getline(cin, donVi);
				DonVi *pDonVi_CanThem = NULL;
				while (pDonVi_CanThem == NULL) {
					cout << "Ban nhap sai ten don vi vui long nhap lai: ";
					cin.sync();
					getline(cin, donVi);
					pDonVi_CanThem = timKiemMotDonVi(ds_DonVi, donVi);
				}
				if (_stricmp(pNhanVien->nhanVien.donVi.c_str(), donVi.c_str()) != 0) {
					pNhanVien->nhanVien.donVi = donVi;
					if (_stricmp(pNhanVien->nhanVien.chucVu.c_str(), "nhan vien") == 0) {
						if (_stricmp(preNhanVien->nhanVien.maNhanVien.c_str(), maNhanVien.c_str()) == 0) {
							pDonVi->nhanVien = pDonVi->nhanVien->next;
							Node_NhanVien *pTemp = pDonVi_CanThem->nhanVien;
							pDonVi_CanThem->nhanVien = preNhanVien;
							preNhanVien->next = pTemp;
						}
						else {
							Node_NhanVien *pTemp = preNhanVien->next;
							preNhanVien->next = pTemp->next;
							Node_NhanVien *pNV = pDonVi_CanThem->nhanVien;
							pDonVi_CanThem->nhanVien = pTemp;
							pTemp->next = pNV;
						}
						pDonVi->soNhanVien--;
						pDonVi_CanThem->soNhanVien++;
					}
					else {
						if (_stricmp(preNhanVien->nhanVien.maNhanVien.c_str(), maNhanVien.c_str()) == 0) {
							pDonVi->canBo = pDonVi->canBo->next;
							Node_NhanVien *pTemp = pDonVi_CanThem->canBo;
							pDonVi_CanThem->canBo = preNhanVien;
							preNhanVien->next = pTemp;
						}
						else {
							Node_NhanVien *pTemp = preNhanVien->next;
							preNhanVien->next = pTemp->next;
							Node_NhanVien *pCB = pDonVi_CanThem->canBo;
							pDonVi_CanThem->canBo = pTemp;
							pTemp->next = pCB;
						}
					}
				}
				cout << "Cap nhat thanh cong !" << endl;
				break;
			}
			case 10: {
				cout << "Nhap ngay Bat dau lam viec: ";
				cin.ignore();
				getline(cin, pNhanVien->nhanVien.ngayBatDauLamViec);
				while (!check_NgayThangNam(pNhanVien->nhanVien.ngayBatDauLamViec)) {
					cout << "Ngay thang nam khong hop le vui long nhap lai(dd/mm/yyyy): ";
					cin.ignore();
					getline(cin, pNhanVien->nhanVien.ngayBatDauLamViec);
				}
				cout << "Cap nhat thanh cong !" << endl;
				break;
			}
			case 11: {
				break;
			}
			}
		} while (LuaChon != 11);
		return 0;
	}
}

int main()
{
	ifstream input;
	input.open("NhanVien.txt", ios_base::in);
	if (input.fail()) {
		cout << "Failed to open this file!" << endl;
		system("pause");
		return -1;
	}
	DonVi *ds_DonVi;
	create_LinkList_DonVi(ds_DonVi);
	cin.sync();
	int n = DocFile(input, ds_DonVi);
	if (n == -1) {
		cout << "file rong! Vui long them thong tin vao file hoac chon 2 de them nhan vien vao cong ty!" << endl;
		/*	system("pause");
			return -1;*/
	}
	float lua_Chon;
	int Lua_Chon;
	do
	{
		cout << "-------------------------------------------menu----------------------------------------------" << endl;
		cout << "1. Hien thi cac thong tin co ban ve BKCorporation?" << endl;
		cout << "2. Tim kiem thong tin cua nhan vien?" << endl;
		cout << "3. Hien thi tinh trang lam viec cua nhan vien?" << endl;
		cout << "4. Hien thi thong tin cua mot don vi?" << endl;
		cout << "5. Them nhan vien moi?" << endl;
		cout << "6. Cap nhat thong tin co ban cua mot nhan vien?" << endl;
		cout << "7. Thoat!" << endl;
		cout << "Ban chon: ";
		cin >> lua_Chon;
		Lua_Chon = (int)lua_Chon;
		if ( cin.fail() || lua_Chon < 1.0 || lua_Chon > 7.0 || lua_Chon != Lua_Chon) { //neu khong phai la so nguyen
			cin.clear(); // bo qua co loi
			cin.ignore(32767, '\n'); //xoa di tat ca cac ki tu trong bo nho dem den khi gap \n
			system("cls");
			cout << "Ban chon sai! vui long thu lai!" << endl;
		}
		else
		{
			system("cls");
			switch (Lua_Chon)
			{
			case 1: {
				cout << "Thong tin co ban ve cong ty BKCorporation: " << endl;
				clock_t start = clock();
				XuatThongTinCoBanVeCongTy(ds_DonVi);
				clock_t finish = clock();
				cout << "\nThoi gian thuc hien: " << (double)(finish - start) / CLOCKS_PER_SEC << "s" << endl;
				break;
			}
			case 2: {
				if (ds_DonVi == NULL)
				{
					cout << "Danh sach cong ty rong!" << endl;
					break;
				}
				cout << "Nhap thong tin tim kiem: ";
				string giaTriTimKiem;
				cin.ignore();
				getline(cin, giaTriTimKiem);
				vector<string> vet;
				XuLyXauTK(vet, giaTriTimKiem);
				Node_NhanVien *pNode = NULL;
				clock_t start = clock();
				Search(ds_DonVi, vet);
				clock_t finish = clock();
				cout << "\nThoi gian thuc hien: " << (double)(finish - start) / CLOCKS_PER_SEC << "s" << endl;
				break;
			}
			case 3: {
				if (ds_DonVi == NULL) {
					cout << "Danh sach cong ty rong!" << endl;
					break;
				}
				cout << "Nhap ma nhan vien: ";
				string maNhanVien;
				cin.ignore();
				getline(cin, maNhanVien);
				clock_t start = clock();
				HienThiTrangThaiLamViec(ds_DonVi, maNhanVien);
				clock_t finish = clock();
				cout << "\nThoi gian thuc hien: " << (double)(finish - start) / CLOCKS_PER_SEC << "s" << endl;
				break;
			}
			case 4: {
				if (ds_DonVi == NULL) {
					cout << "Danh sach cong ty rong!" << endl;
					break;
				}
				DonVi *pDanhSachDonVi = ds_DonVi;
				int n = 1;
				cout << "Danh sach cac don vi: " << endl;
				while (true)
				{
					cout << n << ". " << pDanhSachDonVi->tenDonVi << endl;
					n++;
					if (pDanhSachDonVi->next == ds_DonVi) break;
					pDanhSachDonVi = pDanhSachDonVi->next;
				}
				string tenDonVi;
				cout << "Nhap ten don vi can hien thi: ";
				cin.ignore();
				getline(cin, tenDonVi);
				clock_t start = clock();
				xuatThongTinCoBanVeMotDonVi(ds_DonVi, tenDonVi);
				clock_t finish = clock();
				cout << "\nThoi gian thuc hien: " << (double)(finish - start) / CLOCKS_PER_SEC << "s" << endl;
				break;
			}
			case 5: {
				ThemMotNhanVien(ds_DonVi);
				break;
			}
			case 6: {
				if (ds_DonVi == NULL) {
					cout << "Danh sach cong ty rong!" << endl;
					break;
				}
				cout << "Nhap ma nhan vien: ";
				cin.ignore();
				string maNhanVien;
				getline(cin, maNhanVien);
				int n = UpdateInfo_NhanVien(ds_DonVi, maNhanVien);
				if (n == 0) {
					cout << "Cap nhat thong tin thanh cong!" << endl;
				}
				else
				{
					if (n == -1) cout << "Khong co nhan vien mang ma nay trong cong ty." << endl;
				}
				break;
			}
			case 7: {
				break;
			}
			}
		}
	} while (Lua_Chon != 7);
	input.close();// dong file
	system("pause");
	return 0;
}

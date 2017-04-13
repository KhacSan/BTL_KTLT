#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<iomanip>
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

//đọc thông tin 1 nhân viên từ file
void DocThongTinMotNhanVien(ifstream &input,NhanVien &nhanvien) {
	string str;
	getline(input,str);
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
	ThoiGian thoiGianLamViec;
	string temp;
	DocThoiGianLamViec(input, thoiGianLamViec);
	getline(input, temp);
	nhanvien.DS_ThoiGianLamViec.push_back(thoiGianLamViec);
/*	while (true)
	{
		DocThoiGianLamViec(input, thoiGianLamViec);
		getline(input, temp);
		nhanvien.DS_ThoiGianLamViec.push_back(thoiGianLamViec);
		if (input.eof()) break;
	}*/

}

void DocFile(ifstream &input, NhanVien &nhanvien) {
	
	DocThongTinMotNhanVien(input, nhanvien);
	
 }

void xuatThoiGian(ThoiGian thoiGian) {
	cout << "Ngay : " << thoiGian.ngayThangNam << "," << thoiGian.gioDen << ":" << thoiGian.phutDen << "," 
		 << thoiGian.gioVe << ":" << thoiGian.phutVe << endl;
}

void display(NhanVien nhanvien) {
	string str;
	cout << "Thong tin nhan vien:"<<endl;
	cout << "Ho: " << nhanvien.ho << endl;
	cout << "Ten: " << nhanvien.ten << endl;
	cout << "Don vi: " << nhanvien.diaChi << endl;
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

int main()
{
	ifstream input;
	input.open("NhanVien.txt", ios_base::in);
	NhanVien nhanvien;
	DocFile(input, nhanvien);
	display(nhanvien);
	input.close();
	system("pause");
	return 0;
}
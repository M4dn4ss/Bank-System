#include <iostream>
#include <fstream>
#include <cstdlib>
#include <clocale>
using namespace std;


class Hesap_bilgi
{
private:
	char hesap_numarasi[20];
	char ad[10];
	char soyad[10];
	float toplam_miktar;
public:
	void veri_oku();
	void veri_goster();
	void dosya_yaz();
	void dosya_oku();
	void dosya_ara();
	void dosya_degistir();
	void dosya_sil();
};

void Hesap_bilgi::veri_oku()
{
	cout << "\nHesap numarası gir: ";
	cin >> hesap_numarasi;
	cout << "İsminizi girin: ";
	cin >> ad;
	cout << "Soyadınızı girin: ";
	cin >> soyad;
	cout << "Toplam miktar girin: ";
	cin >> toplam_miktar;
	cout << endl;
	cout << "Kayıt girildi." << endl;

}

void Hesap_bilgi::veri_goster()
{
	cout << "Hesap Numarası: " << hesap_numarasi << endl;
	cout << "Ad: " << ad << endl;
	cout << "Soyad: " << soyad << endl;
	cout << "Toplam Miktar: " << toplam_miktar << endl;
	cout << "----------------------------------" << endl;
}

void Hesap_bilgi::dosya_yaz()
{
	ofstream outfile;
	outfile.open("kayıt.banka", ios::binary | ios::app);
	veri_oku();
	outfile.write(reinterpret_cast<char*>(this), sizeof(*this));
	outfile.close();
}

void Hesap_bilgi::dosya_oku()
{
	ifstream infile;
	infile.open("kayıt.banka", ios::binary);
	if (!infile)
	{
		cout << "Dosya bulunamadı." << endl;
		return;
	}

	cout << "\n***Dosyadaki Veri***" << endl;
	while (!infile.eof())
	{
		if (infile.read(reinterpret_cast<char*>(this), sizeof(*this)))
		{
			veri_goster();
		}
	}
	infile.close();
}

void Hesap_bilgi::dosya_ara()
{
	int n;
	ifstream infile;
	infile.open("kayıt.banka", ios::binary);
	if (!infile)
	{
		cout << "Dosya bulunamadı." << endl;
		return;
	}
	infile.seekg(0, ios::end);
	int sayac = infile.tellg() / sizeof(*this);
	cout << "\n Dosyada " << sayac << " tane kayıt var.";
	cout << "\n Arama yapmak kayıt numarası girin: ";
	cin >> n;
	infile.seekg((n - 1) * sizeof(*this));
	infile.read(reinterpret_cast<char*>(this), sizeof(*this));
	veri_goster();


}

void Hesap_bilgi::dosya_degistir()
{
	int n;
	fstream iofile;
	iofile.open("kayıt.banka", ios::in | ios::binary);
	if (!iofile)
	{
		cout << "Dosya bulunamadı." << endl;
		return;
	}
	iofile.seekg(0, ios::end);
	int sayac = iofile.tellg() / sizeof(*this);
	cout << "\n Dosyada " << sayac << " tane kayıt var.";
	cout << "\n Değiştirmek istediğiniz dosya numarasını girin: ";
	cin >> n;
	iofile.seekg((n - 1) * sizeof(*this));
	iofile.read(reinterpret_cast<char*>(this), sizeof(*this));
	cout << n << " numaralı kayıt şu veriye sahiptir." << endl;
	veri_goster();
	iofile.close();
	iofile.open("kayıt.banka", ios::out | ios::in | ios::binary);
	cout << "\nDeğiştirmek için veri girin. " << endl;
	veri_oku();
	iofile.write(reinterpret_cast<char*>(this), sizeof(*this));
	cout << "Kayıt değiştirildi." << endl;
}

void Hesap_bilgi::dosya_sil()
{
	int n;
	ifstream infile;
	infile.open("kayıt.banka", ios::binary);
	if (!infile)
	{
		cout << "Dosya bulunamadı." << endl;
		return;
	}
	infile.seekg(0, ios::end);
	int sayac = infile.tellg() / sizeof(*this);
	cout << "\n Dosyada " << sayac << " tane kayıt vardır.";
	cout << "\n Silmek için bir kayıt numarası girin: ";
	cin >> n;
	fstream tmpfile;
	tmpfile.open("tmpfile.banka", ios::out | ios::binary);
	infile.seekg(0);
	for (int i = 0; i < sayac; i++)
	{
		infile.read(reinterpret_cast<char*>(this), sizeof(*this));
		if (i == (n - 1))
			continue;
		tmpfile.write(reinterpret_cast<char*>(this), sizeof(*this));
	}
	infile.close();
	tmpfile.close();
	remove("kayıt.banka");
	rename("tmpfile.banka", "kayıt.banka");
	cout << "Kayıt silindi" << endl;


}

int main()
{
	setlocale(LC_ALL, "Turkish");
	Hesap_bilgi H;
	int secim;
	cout << "***HESAP BİLGİ SİSTEMİ***" << endl;
	while (true)
	{
		cout << "Aşağıdaki seçeneklerden birisini seçin." << endl;
		cout << "\n\t1-->Kayıt ekle";
		cout << "\n\t2-->Kayıt göster";
		cout << "\n\t3-->Kayıt ara";
		cout << "\n\t4-->Kayıt güncelle";
		cout << "\n\t5-->Kayıt sil";
		cout << "\n\t6-->Çıkış";
		cout << "\nSeçiminizi girin: ";
		cin >> secim;
		switch (secim)
		{
		case 1 :
			H.dosya_yaz();
			system("pause");
			system("cls");
			break;
		case 2:
			H.dosya_oku();
			system("pause");
			system("cls");
			break;
		case 3:
			H.dosya_ara();
			system("pause");
			system("cls");
			break;
		case 4:
			H.dosya_degistir();
			system("pause");
			system("cls");
			break;
		case 5:
			H.dosya_sil();
			system("pause");
			cout << "Kayıt silindi." << endl;
			system("cls");
			break;
		case 6:
			exit(0);
			break;
		default:
			cout << "\nDoğru seçim girin.";
			exit(0);
		}
	}
	system("pause");
}


# Bioinformatics 
by @celineuygun @dilaranarin @yucerece

## İçindekiler
```
1. Giriş
2. Analiz
3. Model Tasarımı
  3.1. Hash Tablosu
  3.2. DNA Sarmalının Bastırılması
  3.3. Program Sonuçları ve Karmaşıklık 
4. Sonuç
5. Kaynakça
```

## 1. Giriş
Bu projeyle, moleküler biyoloji alanındaki deneysel verilerin büyük ve elle
işlenmesinin zor olması nedeniyle bilgisayar teknolojileri yardımıyla DNA dizilerini saklayan
geniş veri tabanları oluşturarak gen araması yapılması ve genler arasındaki
benzerlik/farklılıkların bulunması amaçlanır.

Projemiz içerisinde 5 farklı komut kullanılmaktadır. İlk olarak metin dosyası
içerisinde veriler okunarak dosya bilgileri bastırılır. DNA dizileri incelenen kişilerin hatasız
verileri de bastırılırken üçüncü olarak ise hatalı veriler bastırılır. Girilen parametrelere göre
DNA benzerlikleri tespit edilir ve son olarak ise istenen gen dizisine sahip kişilerin verileri
bastırılır.

Biyoinformatik DNA/RNA/protein yapısının okunması, genetik
faktörlerin hastalık yatkınlığına etkilerini ortaya çıkarılması, türler arasındaki
benzerlik/farklılıkların tespit edilmesi vb. alanlarda kullanılmaktadır. Biyoinformatik alanında
yapılmış en önemli projelerden olan İnsan Genom Projesi, yaklaşık 25.000 insanın gen
diziliminin tümünün keşfedilmesi, DNA alt birimlerinin sırasının tespit edilmesi ve bu
bilgilerin diğer alanlarda kullanılmasını amaçlamıştır. Bu proje ve diğer yapılan çalışmalar,
birlikte DNA dizilimlerindeki gen benzerlik/farklılıkları tespit ederek saptanan hastalıkların
tedavisinde kullanılmaktadır.

## 2. Analiz

Biyoinformatik projesi 3 farklı klasör içermektedir. Test adlı klasör ana test koduyla
birlikte test metin dosyası içermektedir. Data klasörü ana programda çalıştırılacak tüm
bireylerin DNA dizilimleri içeren metin dosyası içerirken src klasörü ise ana kod dosyası ve
headerlarıyla birlikte 2 adet daha kaynak kod dosyası içermektedir. Programı çalıştırmak için
ilk olarak terminal üzerinden proje klasöründe kodları bulunduran src klasörü açılır ve make
komutu ile derlenir. Sonrasında oluşan ./main dosyasıyla, verilerin saklandığı .txt uzantılı
dosya ismi girilir. Tüm proje C diliyle yazılmış olup Linux sistemi üzerinden derlenmiş ve
çalıştırılmıştır. Olası bellek sızıntılarını ortadan kaldırmak amacıyla Valgrind kullanılarak test
edilmiştir.

print_double_helix fonksiyonları, programı kullanırkenkullanıcı için DNA dizilerini görsel 
olarak açıklama amacıyla eklenmiştir. Bu iki fonksiyon
sayesinde kullanıcı doğru ve yanlış DNA dizilimine sahip insanların DNA sarmalını görsel bi
şekilde görebilir ve aynı zamanda yanlış DNA dizilimine sahip insanların DNA sarmalını
gösterirken ayrıca hatalı eşleşmelerin yerini kolaylıkla tespit etmeyi sağlar. find_binary ise
istenen kimlik numarasına sahip kişiyi binary search kullanarak bulur ve o kişinin bilgilerini
print_double_helix fonksiyonunu kullanarak yazdırır.

Bu projede dizi, struct, linked list ve hash tablosu olmak üzere dört farklı
veri yapısı kullanılmıştır. İstenildiği gibi find_gene_rabinkarp fonksiyonu içerisinde hash
kullanılmasının yanı sıra, verilen parametreye en çok benzeyen kimlik numaralarını bastıran
find_similar_first fonksiyonu için de hash veri yapısı kullanılmıştır.

## 3. Model Tasarımı

### 3.1. Hash Tablosu
find_similar_first fonksiyonunun parametre olarak verilen dizi için veri tabanında en
benzer ilk k değerini geri döndürmesi istenmektedir. Fonksiyon veri tabanını bir defa baştan arayarak
hash tablosu içerisinde tutar ve böylece hash tablosunun ilk k değeri en benzer değerler olarak
geri döndürür.

Hash veri yapısının kullanıldığı ikinci fonksiyon ise, içerisinde finger_print bulunduran ve
Rabin-Karp string arama algoritmasını kullanan find_gene_rabinkarp fonksiyonudur
Rabinkarp fonksiyonu, find_gene_classic fonksiyonu ile aslında
aynı işlevi görür, parametre olarak verilen gen dizine sahip bireylerin kimlik bilgilerini
döndürmektir. Fakat gene_classic, lineer bir arama yaparken, rabinkarp hash yöntemini
kullanır. Bu sebepten dolayı aralarında işlem süresi farkı açığa çıkar.

### 3.2. DNA Sarmalının Bastırılması
print_double_helix ve print_double_helix_corr fonksiyonları ile birlikte kişilerin verilerini
DNA’larının çift sarmallı yapısı ile bastırılarak hem hatalı veriye sahip kişilerin eşleşme
hataları çok daha rahat görülebilir hem de görsel olarak programın daha estetik bir çıktı
vermesi sağlanmış olur.

### 3.3. Program Sonuçları ve Karmaşıklık
Program 5 komut ile çalışmaktadır. Kişi verilerini
içeren dosya bilgilerini bastırabilir. Hatalı ve hatasız DNA'ya sahip
kişilerin bilgilerini bastırarak istenen kimlik numaralı kişilerin ayrıntılı DNA bilgisini
gösterebilir. Girilen verilere göre DNA benzerliklerini bulabilir ve
son olarak aynı gene sahip kişileri tespit edebilir.

Struct veri yapısında olan read_person_file fonksiyonu kişi verilerini satır satır
okurken kişi bilgilerini O(N) sürede uygun struct’a kaydeder. print_database,
print_double_helix ve print_double_helix_corr fonksiyonları ise struct yapılarında tutulan
kişi ve kişilerin verilerini baştan sona O(N) karmaşıklığında bastırır. find_binary fonksiyonu
ise parametre olarak verilen kimlik numarasındaki kişiyi ikili arama algoritması ile O(logN)
karmaşıklığında bularak bilgilerini yazdırır. İki gen dizisinin benzerliğini Levenshtein
uzaklığı (minimum silme, ekleme ve değiştirme işlem sayısı) kullanarak bulunan
find_distance fonksiyonu ise dynamic programming algoritmasını kullanarak
O(len(seq1).len(seq2)) zaman kompleksitesinde çalışmaktadır, implement edilen matriksten
dolayı da yer kompleksitesi O(len(seq1).len(seq2))’dir. find_similar_first ise O(N^2) de
çalışarak uzaklığı en düşük olan ilk kişinin bilgilerini döndürür. İçerisinde finger_print
bulunduran ve Rabin-Karp string arama algoritmasını kullanan find_gene_rabinkarp
fonksiyonun beklenen karmaşıklığı O(N+M), en kötü durumda ise O(N*M) karmaşıklığında
çalışmaktadır. find_gene_classic fonksiyonunun ise beklenen karmaşıklığı O(N)’dir.

## 4. Sonuç
Bu proje bir veri dosyasındaki bilgileri okuyup, onları uygun şekilde sınıflandırarak
hatalı ve hatasız olanları farklı struct yapıları içinde saklar. Arama fonksiyonları ile de çokça
veri içeren dosyalarda bile istenen özellikler doğrultusundaki veriler kolayca
bulabilmektedir. Bu projenin asıl amacı, bilgisayar teknolojileri yardımıyla DNA dizilerini
saklayan geniş veri tabanları oluşturarak gen araması yapılması ve genler arasındaki
benzerlik/farklılıkların bulunmasıdır. Projeye daha fazla fonksiyon ekleyerek, daha geniş
çaplı bir gen arama programı olarak kullanılabilir. Mesela, aranan bir kişinin bilgilerinin
yanlış olduğunun fark edilmesi durumunda, program üzerinden değişiklik yapmasını
sağlayan bir hale getirilebilir. Projede verilen veri tabanı sadece yanlış eşleşmeleri içeriyor
fakat diğer DNA hatalarını da kapsayacak bir şekilde iyileştirilebilir. Kişinin sadece ilk gen
dizisine bakarak yazdığımız fonksiyonlar her iki diziye de bakacak şekilde değiştirilebilir.
Struct yapısına daha çok şey eklenerek program hem daha kısa hem de daha kapsamlı bir
hale getirilebilir. find_distance fonksiyonunda kullanılan dynamic programming algoritması
matrikste sadece en alt 2 satır kullanılacak şekilde değiştirilebilir böylece yer karmaşıklığı
O(max(len(seq1), len(seq2))) olarak azaltılabilir. Bunlar gibi çeşitli değişiklikler yapılarak
daha çok amaca hizmet eden daha etkili bir program elde edilebilir.

## 5. Kaynakça
```
[1] Yalınkılıç, S. B. (2020, 3 Haziran). BİYOİNFORMATİK VE BİYOLOJİDEKİ KULLANIM ALANLARI. Moleküler Biyoloji ve Genetik. https://molekulerbiyolojivegenetik.org/biyoinformatik-ve-biyolojideki-kullanim-alanlari/
[2] Wikipedia contributors. (2006, 21 Şubat). Biyoenformatik. Vikipedi. https://tr.wikipedia.org/wiki/Biyoenformatik
[3] Levenshtein Distance Algorithm better than O(n*m)? (2010, 30 Ekim). StackOverflow. https://stackoverflow.com/questions/4057513/levenshtein-distance-algorithm-better-than-onm
[4] GeeksforGeeks. (2021, 28 Mayıs). Rabin-Karp Algorithm for Pattern Searching. https://www.geeksforgeeks.org/rabin-karp-algorithm-for-pattern-searching/
[5] Back To Back SWE. (2019, 11 Ocak). Edit Distance Between 2 Strings - The Levenshtein Distance (“Edit Distance” on LeetCode) [Video]. Youtube. https://www.youtube.com/watch?v=MiqoA-yF-0M
```

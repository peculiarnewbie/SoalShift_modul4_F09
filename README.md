# SoalShift_modul4_F09

### Arif Rahman (05111740000089)

### Choirur Roziqin (05111640000178)

## Soal 1
Semua nama file dan folder harus terenkripsi
Enkripsi yang Atta inginkan sangat sederhana, yaitu Caesar cipher. Namun, Kusuma mengatakan enkripsi tersebut sangat mudah dipecahkan. Dia menyarankan untuk character list diekspansi,tidak hanya alfabet, dan diacak. Berikut character list yang dipakai:

qE1~ YMUR2"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\8s;g<{3.u*W-0`

Misalkan ada file bernama “halo” di dalam folder “INI_FOLDER”, dan key yang dipakai adalah 17, maka:
“INI_FOLDER/halo” saat belum di-mount maka akan bernama “n,nsbZ]wio/QBE#”, saat telah di-mount maka akan otomatis terdekripsi kembali menjadi “INI_FOLDER/halo” .
Perhatian: Karakter ‘/’ adalah karakter ilegal dalam penamaan file atau folder dalam *NIX, maka dari itu dapat diabaikan


hasil pengerjaan:

before:

![](/pics/before.png)


after:

![](/pics/after.png)


cara pengerjaan:
menggunakan 3 fungsi yaitu getattr, readdir, dan read. melakukan encrypt pada 3 fungsi tersebut, dan decrypt pada readdir bagian file. enkripsi dan dekripsi sendiri dilakukan dengan mengkopi array path ke array lain lalu mencari posisi masing-masing karakter pada karakter list dan menginput karakter di sisi ke 17nya ke array lain lalu menjadikan array tersebut sebagai output. dekripsi melakukan hal serupa namun mengambil karakter 17 sebelumnya.

ada 2 pengecualian untuk enkripsi dan dekripsi, yaitu karakter '/'  dan input '.' maupun '..' yang akan di ignore apabila bertemu.


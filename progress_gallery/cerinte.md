# Lista cu cerințele de pe [github](https://github.com/Oepeling/poo/tree/master/Laborator)
+ snippeturi din cod.
## Cerințe generale
- [x] folosirea coerentă și motivată a specificatorilor de acces (private, protected, public)

Exemplu, clasa `sphere`:

```cpp
class sphere : public hittable {
private:
    point3 center;
    double radius;
    shared_ptr<material> mat;
public:
    sphere(const point3& center, double radius, shared_ptr<material> mat);

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override;
};
```

- Starea internă a unei sfere este protejată prin modificatorul de acces `private`, prevenind accesul direct și asigurând integritatea datelor.
- Constructorul și metoda `hit` sunt expuse public pentru a permite instanțierea și manipularea corectă a obiectelor de tip `sphere` în cadrul proiectului.

---


- [x] folosirea coerentă și motivată a const și referință (&)
- În constructorul `sphere`, avem argumentul `const point3& center`.
- Utilizarea referinței (&) evită copierea inutilă a obiectelor la apelul funcției, ceea ce optimizează performanța.
- Adăugarea const indică faptul că funcția nu modifică obiectul transmis prin referință, asigurând protecția datelor.
---
- [x] teste
- există atât teste cu `Catch2`, pentru clasele unde pot fi implementate unit tests
- vizualizare live a creării imaginii
---
- [x] să nu aveți memorie reziduală (memory leaks), în caz că faceți alocări dinamice
- Prin utilizarea `shared_ptr` pentru membrii dinamici precum `mat` în clasa `sphere`, se asigură gestionarea automată a duratei de viață a obiectelor alocate dinamic.
## Cerințe echivalente tema 1
- [x] câmpuri + metode publice și private

În clasa `camera`:
- câmpuri private: `int image_height;` (se calculează intern din proprietatea `image_width` și `aspect ratio`)
- metode private: `void initialize();`
- metode public: `void render(const hittable& world);` - utilizează toate metodele private pentru a randa scena
---
- [x] constructori

Constructorii clasei `vec3`:
```cpp
`   vec3();
    vec3(double x, double y, double z);
    vec3(const vec3& v);
```
---
- [x] destructori

Destructori virtuali:
```cpp
virtual ~material() = default;
```
---
- [x] supraîncărcare de operatori (inclusiv operatorii >> -- citire și << -- afișare)
Foarte mulți în clasa `vec3`:
```cpp
std::ostream& operator<<(std::ostream& out, const vec3& v);
vec3 operator+(const vec3& v, const vec3& u);
vec3 operator-(const vec3& v, const vec3& u);
vec3 operator*(double a, const vec3& v);
```
## Cerințe echivalente tema 2
- [x] moșteniri
Toate tipurile de material: `lambertian`, `metal`, `dielectric` moștenite din `material`:
```cpp
class lambertian : public material {
    //
}
```
---
- [x] funcții virtuale
De exemplu, în `material`:
```cpp
class material {
public:
    virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const {
        return false;
    }
    //
};
```
---
- [x] excepții

În `camera::initialize()`:
```cpp
void camera::initialize() {
    try {
    //
        if (aspect_ratio <= 0.0) {
            throw std::invalid_argument("aspect_ratio must be positive");
        }
    //
    } catch (const std::exception& e) {
        throw;
    }
}
```
Aici se inițializează camera prin proprietățile ei. Dacă acestea nu sunt valide, eroarea se propagă în `camera::render`, după care în `main`, unde este prinsă.
---
- [x] dynamic_cast sau static_cast
```cpp
image_height = static_cast<int>(image_width / aspect_ratio);
```
---
- [x] **bonus** clasă abstractă
Mai multe, exemplu `hittable`
```cpp
class hittable {
public:
    virtual ~hittable() = default;

    virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
};
```
## Cerințe echivalente tema 3
- [x] minim o funcție șablon și o clasă șablon
    - [x] minim un atribut `T` care depinde de `T`
    - [x] minim o funcție membru care să depindă de `T`

```cpp
template <typename T>
class Property {
    T value_;
public:
//
    T& get() {
        return value_;
    }

    void set(const T& v) {
        value_ = v;
    }
//
};
```

În `camera` aveam mai multe proprietăți pe care vreau să le accesez (e.g, `image_width`, `aspect_ratio`), iar, în loc de a face settere și gettere pentru fiecare, mai bine am făcut o clasă șablon pentru proprietate.
    - [x] minim o funcție normală/liberă de template

```cpp
template <typename T>
void clamp(Property<T>& prop, T min_val, T max_val) {
    T value = prop.get();
    if (value < min_val) value = min_val;
    if (value > max_val) value = max_val;
    prop.set(value);
}
```

Această funcție se asigură proprietatea e în intervalul dorit.

---
- [x] 2 design patterns (3 dacă e și singleton)
- `camera` e singleton
- Scena este creată într-un factory
(îmi pare rău, nu am mai avut altă idee)
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
- [ ] câmpuri + metode publice și private
- [ ] constructori
- [ ] destructori
- [ ] supraîncărcare de operatori (inclusiv operatorii >> -- citire și << -- afișare)
## Cerințe echivalente tema 2
- [ ] moșteniri
- [ ] funcții virtuale
- [ ] excepții
- [ ] dynamic_cast sau static_cast
- [ ] **bonus** clasă abstractă
## Cerințe echivalente tema 3
- [ ] minim o funcție șablon și o clasă șablon
    - [ ] minim un atribut `T` care depinde de `T`
    - [ ] minim o funcție membru care să depindă de `T`
    - [ ] minim o funcție normală/liberă de template
- [ ] 2 design patterns (3 dacă e și singleton)
// g++ -g tests.cpp -o tests
// valgrind --leak-check=full ./tests

#include "mini_test.h"
#include "messineria.h"

/*
 * Crea una messineria de int vacia y no agrega elementos
 */
void check_crear_messineria_vacia() {
  Messineria<int> messi;

  ASSERT_EQ(messi.esVacia(), true);

  ASSERT_EQ(messi.tamanio(), 0);
}
void check_gol_de_messi_messineria_vacia() {
    Messineria<int> messi;
    int a = 1;
    messi.golDeMessi(a);
    ASSERT_EQ(messi.esVacia(), false);
    ASSERT_EQ(messi.tamanio(), 1);
}

void check_golesMessi_aumentanTamanio(){
    Messineria<int> messi;
    int golesMessi = 10;
    for (int i=0; i<golesMessi; i++) {
        messi.golDeMessi(i);
    }
    messi.alabarMessi();
    messi.alabarMessi();
    messi.alabarMessi();
    messi.alabarMessi();
    messi.alabarMessi();
    messi.alabarMessi();
    messi.alabarMessi();
    messi.alabarMessi();
    messi.alabarMessi();
    messi.alabarMessi();
    messi.alabarMessi();
    messi.alabarMessi();
    ASSERT_EQ(messi.adeptoAlabando(), 2);
}

void check_muestra_Bien(){
    Messineria<int> messi;
    messi.golDeMessi(0);
    ASSERT_EQ(messi.adeptoAlabando(), 0);
}

void check_Alabar_Anda_Bien(){
    Messineria<int> messi;
    messi.golDeMessi(0);
    messi.golDeMessi(20);
    messi.golDeMessi(2);
    messi.olvideAlabarloUnPocoMas();
    messi.olvideAlabarloUnPocoMas();
    messi.olvideAlabarloUnPocoMas();
    messi.olvideAlabarloUnPocoMas();
    messi.olvideAlabarloUnPocoMas();
    messi.olvideAlabarloUnPocoMas();
    messi.olvideAlabarloUnPocoMas();
    messi.olvideAlabarloUnPocoMas();
    messi.olvideAlabarloUnPocoMas();
    messi.olvideAlabarloUnPocoMas();
    messi.olvideAlabarloUnPocoMas();
    messi.olvideAlabarloUnPocoMas();

    ASSERT_EQ(messi.adeptoAlabando(), 0);
}

void check_OlvideAlabar_Anda_Bien(){
    Messineria<int> messi;
    messi.golDeMessi(0);
    messi.golDeMessi(20);
    messi.golDeMessi(21);
    messi.golDeMessi(22);
    messi.golDeMessi(23);
    messi.olvideAlabarloUnPocoMas();
    messi.olvideAlabarloUnPocoMas();
    messi.olvideAlabarloUnPocoMas();
    messi.olvideAlabarloUnPocoMas();
    ASSERT_EQ(messi.adeptoAlabando(), 20);
}

void check_elegido(){
    Messineria<int> messi;
    messi.golDeMessi(0);
    messi.golDeMessi(10);
    messi.golDeMessi(17);
    messi.golDeMessi(27);
    messi.golDeMessi(30);
    messi.golDeMessi(35);
    messi.escogerElegido();
    messi.interrumpirTurno();
    messi.alabarMessi();
    messi.alabarMessi();
    ASSERT_EQ(messi.hayElegido(), true);
    ASSERT_EQ(messi.dameElegido(), 0);
    ASSERT_EQ(messi.adeptoAlabando(), 17);
}

void check_constructorCopia() {
    Messineria<int> messi;
    messi.golDeMessi(0);
    messi.golDeMessi(20);
    messi.golDeMessi(2);
    messi.alabarMessi();
    messi.alabarMessi();
    Messineria<int> messi2(messi);
    ASSERT_EQ(messi2.adeptoAlabando(), 2);
}

void check_golesCristiano(){
    Messineria<int> messi;
    int golesMessi = 20, golesCristiano = 10;
    for (int i=0; i<golesMessi; i++) {
        messi.golDeMessi(i);
        ASSERT_EQ(messi.tamanio(), i+1);
    }
    for (int i=0; i<golesCristiano; i++) {
        messi.golDeCristiano(i);
        ASSERT_EQ(messi.tamanio(), 20-i-1);
    }
}

void check_traidor_TodoPiola(){
    Messineria<int> messi;
    messi.golDeMessi(0);
    messi.golDeMessi(10);
    messi.golDeMessi(17);
    messi.golDeMessi(18);
    messi.golDeMessi(19);
    messi.golDeMessi(20);
    messi.alabarMessi();
    messi.alabarMessi();
    messi.escogerElegido();
    messi.alabarMessi();
    messi.alabarMessi();
    messi.alabarMessi();
    messi.traidor();
    ASSERT_EQ(messi.adeptoAlabando(), 20)
    ASSERT_EQ(messi.hayElegido(), false);
    messi.alabarMessi();
    messi.alabarMessi();
    messi.alabarMessi();
    ASSERT_EQ(messi.adeptoAlabando(), 18)
}

void check_son_iguales(){
Messineria<int> messi;
    messi.golDeMessi(0);
    messi.golDeMessi(10);
    messi.golDeMessi(17);
    messi.golDeMessi(18);
    messi.golDeMessi(19);
    messi.golDeMessi(20);
    messi.alabarMessi();
    messi.alabarMessi();
Messineria<int> messi2;
    messi2.golDeMessi(17);
    messi2.golDeMessi(18);
    messi2.golDeMessi(19);
    messi2.golDeMessi(20);
    messi2.golDeMessi(0);
    messi2.golDeMessi(10);
    messi2.alabarMessi();
    messi2.alabarMessi();
    ASSERT_EQ(messi==messi2, false);
}

void check_operator_andaBarbaro(){
    Messineria<int> messi;
    messi.golDeMessi(0);
    messi.golDeMessi(20);
    messi.golDeMessi(2);
    messi.alabarMessi();
    messi.alabarMessi();
    Messineria<int> messi2(messi);
    bool res;
    res = (messi == messi2);
    ASSERT_EQ(res, true);
}

int main() {
  RUN_TEST(check_crear_messineria_vacia);
  RUN_TEST(check_gol_de_messi_messineria_vacia);
  RUN_TEST(check_golesMessi_aumentanTamanio);
  RUN_TEST(check_muestra_Bien);
  RUN_TEST(check_Alabar_Anda_Bien);
  RUN_TEST(check_OlvideAlabar_Anda_Bien);
  RUN_TEST(check_elegido);
  RUN_TEST(check_golesCristiano);
  RUN_TEST(check_traidor_TodoPiola);
  RUN_TEST(check_operator_andaBarbaro);
  RUN_TEST(check_son_iguales);
  return 0;
}


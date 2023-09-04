module Spec where
import PdePreludat
import Library
import Test.Hspec

correrTests :: IO ()
correrTests = hspec $ do
  describe "TEST FUNCION 1" $ do
    it "El danio potencial de Mojo Jojo es de 64" $ do
      danioPotencial mojoJojo `shouldBe` 64
    it "El danio potencial de Princesa es de 89" $ do
      danioPotencial princesa `shouldBe` 89
    it "El danio potencial de Banda Gangrena es de 40" $ do
      danioPotencial bandaGangrena `shouldBe` 40

  describe "TEST FUNCION 2" $ do
    it "Mojo Jojo puede atacar Saltadilla" $ do
      puedeAtacar mojoJojo (Ciudad "Saltadilla" 21) `shouldBe` True
    it "Princesa puede atacar Saltadilla" $ do
      puedeAtacar princesa (Ciudad "Saltadilla" 21) `shouldBe` True
    it "Banda Gangrena no puede atacar Saltadilla" $ do
      puedeAtacar bandaGangrena (Ciudad "Saltadilla" 21) `shouldBe` False

  describe "TEST FUNCION 3" $ do
    it "Bombon puede vencer a Mojo Jojo" $ do
      puedeVencer bombon mojoJojo `shouldBe` True
    it "Burbuja no puede vencer a Princesa" $ do
      puedeVencer burbuja princesa `shouldBe` False

  describe "TEST FUNCION 4" $ do
    it "Princesa es una amenaza de nivel alto" $ do
      esNivelAlto princesa `shouldBe` True
    it "Banda Gangrena no es una amenaza de nivel alto" $ do
      esNivelAlto bandaGangrena `shouldBe` False

  describe "YENDO AL NUTRICIONISTA" $ do
    it "Una chica se queda sin resistencia al consumir sustancia X" $ do
      (resistencia.sustanciaX $ bombon) `shouldBe` 0
    it "Burbuja tiene 20 de resistencia luego de consumir caramelo" $ do
      (resistencia.carameloLiquido $ burbuja) `shouldBe` 20
    it "Seniorita Belo tiene 0 de resistencia luego de consumir caramelo" $ do
      (resistencia.carameloLiquido $ senioritaBelo) `shouldBe` 0
    it "Bellota luego de tomar Gatorei queda igual" $ do 
      gatorei bellota `shouldBe` bellota
    it "Bombon luego de tomar Gatorei queda con 65 puntos de resistencia" $ do
      (resistencia.gatorei $ bombon) `shouldBe` 65
    it "Burbuja toma una cerveza con el señor Silico y queda con 2 amigos" $ do
      (length.amistades.cerveza [silico] $ burbuja) `shouldBe` 2
    it "Bellota toma un ferne' y suma la habilidad de 'Chef de Asados'" $ do
      bellota `shouldSatisfy` (elem "Chef de Asados".habilidades.ferne')
    it "Burbuja toma una cerveza con la señorita Belo y queda con un amigo" $ do
      (length.amistades.cerveza [senioritaBelo] $ burbuja) `shouldBe` 1
    it "Bombon toma 3 shots de vodka y pasa a llamarse 'Bom'" $ do
      (nombreHeroe.vodka.vodka.vodka $ bombon) `shouldBe` "Bom"
    it "Señor Cerdo le entra a la cocucha y queda igual" $ do
      cocucha seniorCerdo `shouldBe` seniorCerdo
    it "Burbuja se toma una cocucha y ya no tiene velocidad" $ do
      burbuja `shouldSatisfy` (notElem "Velocidad".habilidades.cocucha)

  describe "MI VILLANO FAVORITO" $ do
    it "Mojo Jojo ataca Saltadilla 1 vez, la poblacion final es 9" $ do
      atacaCiudad 1 mojoJojo saltadilla `shouldBe` 9
    it "Princesa ataca Saltadilla 1 vez, la poblacion final es 13" $ do
      atacaCiudad 1 princesa saltadilla `shouldBe` 13
    it "Banda Gangrena ataca Saltadilla 1 vez, la poblacion final es 17" $ do
      atacaCiudad 1 bandaGangrena saltadilla `shouldBe` 17
    it "Banda Gangrena ataca Saltadilla 2 veces, la poblacion final es 26" $ do
      atacaCiudad 2 bandaGangrena saltadilla `shouldBe` 26

  describe "¿VEMOS UNO MAS?" $ do
    it "luego del capitulo 1 Saltadilla queda con 9 habitantes " $ do
      darlePlay saltadilla capitulo1 `shouldBe` Ciudad {nombreCiudad = "Saltadilla", habitantes = 9}
    it "luego del capitulo 1 Armadillo queda con 40 habitantes " $ do
      darlePlay armadillo capitulo1 `shouldBe` Ciudad {nombreCiudad = "Armadillo", habitantes = 40}
    it "luego del capitulo 2 Saltadilla queda con 21 habitantes " $ do
      darlePlay saltadilla capitulo2 `shouldBe` Ciudad {nombreCiudad = "Saltadilla", habitantes = 21}
    it "luego del capitulo 2 Armadillo queda con 36 habitantes " $ do
      darlePlay armadillo capitulo2 `shouldBe` Ciudad {nombreCiudad = "Armadillo", habitantes = 36}
    it "luego del capitulo 3 Saltadilla queda con 13 habitantes " $ do
      darlePlay saltadilla capitulo3 `shouldBe` Ciudad {nombreCiudad = "Saltadilla", habitantes = 13}
    it "luego del capitulo 3 Armadillo queda con 40 habitantes " $ do
      darlePlay armadillo capitulo3 `shouldBe` Ciudad {nombreCiudad = "Armadillo", habitantes = 40}
    it "luego del capitulo 4 Saltadilla queda con 21 habitantes " $ do
      darlePlay saltadilla capitulo4 `shouldBe` Ciudad {nombreCiudad = "Saltadilla", habitantes = 21}
    it "luego del capitulo 4 Armadillo queda con 34 habitantes " $ do
      darlePlay armadillo capitulo4 `shouldBe` Ciudad {nombreCiudad = "Armadillo", habitantes = 34}

    it "luego de la temporada 1 Saltadilla queda con 1 habitante " $ do
      maraton saltadilla temporada1 `shouldBe` Ciudad {nombreCiudad = "Saltadilla", habitantes = 1}
    it "luego de la temporada 1 Armadillo queda con 30 habitantes " $ do
      maraton armadillo temporada1 `shouldBe` Ciudad {nombreCiudad = "Armadillo", habitantes = 30}
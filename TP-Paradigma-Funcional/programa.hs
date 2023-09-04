module Library where
import PdePreludat

data Heroe = Heroe {
    nombreHeroe :: String,
    resistencia :: Number,
    habilidades :: [String],
    amistades :: [String]
} deriving (Show,Eq)

data Amenaza = Amenaza {
    nombreAmenaza :: String,
    proposito :: String,
    poder :: Number,
    debilidades :: [String],
    efectoCiudad :: EfectoCiudad
} deriving (Show,Eq)

type EfectoCiudad = Ciudad -> Ciudad

data Ciudad = Ciudad {
    nombreCiudad :: String,
    habitantes :: Number
} deriving (Show,Eq)

bombon = Heroe {
    nombreHeroe = "Bombon",
    resistencia = 55,
    habilidades = ["Luciano Pereyra","Golpes Fuertes"],
    amistades = ["Senior Cerdo","Silico"]
}

burbuja = Heroe {
    nombreHeroe = "Burbuja",
    resistencia = 30,
    habilidades = ["Velocidad","Burbujas"],
    amistades = ["Seniorita Belo"]
}

bellota = Heroe {
    nombreHeroe = "Bellota",
    resistencia = 75,
    habilidades = ["Superfuerza","Velocidad"],
    amistades = []
}

senioritaBelo = Heroe {
    nombreHeroe = "Seniorita Belo",
    resistencia = 10,
    habilidades = ["No mostrar la cara"],
    amistades = ["Burbuja"]
}

seniorCerdo = Heroe {
    nombreHeroe = "Senior Cerdo",
    resistencia = 0,
    habilidades = [],
    amistades = ["Bellota"]
}

silico = Heroe {
    nombreHeroe = "Silico",
    resistencia = 29,
    habilidades = ["Tolerar impares"],
    amistades = ["Bombon","Burbuja"]
}

mojoJojo = Amenaza {
    nombreAmenaza = "Mojo Jojo",
    proposito = "destruir a las Chicas Superpoderosas",
    poder = 70,
    debilidades = ["Velocidad","Superfuerza"],
    efectoCiudad = efectoMojoJojo
}

princesa = Amenaza {
    nombreAmenaza = "Princesa",
    proposito = "ser la unica Chica Superpoderosa",
    poder = 95,
    debilidades = ["Burbujas","Golpes Fuertes"],
    efectoCiudad = efectoPrincesa
}


bandaGangrena = Amenaza {
    nombreAmenaza = "Banda Gangrena",
    proposito = "esparcir el caos y hacer que todos sean flojos y peleen entre ellos",
    poder = 49,
    debilidades = ["Luciano Pereyra","Superfuerza","Kryptonita"],
    efectoCiudad = efectoGangrena
}

-- FUNCION 1

danioPotencial :: Amenaza -> Number
danioPotencial amenaza = poder amenaza - ( (*3) . length . debilidades )  amenaza

-- FUNCION 2

puedeAtacar :: Amenaza -> Ciudad -> Bool
puedeAtacar amenaza ciudad = danioPotencial amenaza > ( (*2) . habitantes ) ciudad

-- FUNCION 3

puedeVencer :: Heroe -> Amenaza -> Bool
puedeVencer heroe amenaza
    | (even.length.proposito) amenaza = resistencia heroe > ( (/2) . danioPotencial) amenaza 
    | otherwise = resistencia heroe > danioPotencial amenaza

-- FUNCION 4

esNivelAlto :: Amenaza -> Bool
esNivelAlto amenaza = 
    ((>50).danioPotencial) amenaza && (even.length.debilidades) amenaza 
        && (notElem "Kryptonita".debilidades) amenaza

-- PARTE 2

-- ENTRADA EN CALOR

-- 1.

esInvulnerable :: Amenaza -> Heroe -> Bool
esInvulnerable amenaza heroe = not $ any (`elem` debilidades amenaza) (habilidades heroe)

-- 2. 

mayorSegun f valor1 valor2
    | f valor1 > f valor2 = valor1
    | otherwise = valor2

maximoSegun f = foldl1 (mayorSegun f)

amenazaPreponderante = maximoSegun poder

listaAmenazas = [mojoJojo,princesa,bandaGangrena]

-- 3.

listaHeroes = [bombon,burbuja,bellota,senioritaBelo,seniorCerdo,silico]

puedenVencer heroes amenaza = map nombreHeroe . filter (`puedeVencer` amenaza) $ heroes

-- 4.

filtroNombreHabilidad :: [Heroe] -> [Heroe]
filtroNombreHabilidad = 
    filter (\x -> ((=='B').head.nombreHeroe) x && ((>1).length.habilidades) x)

-- YENDO AL NUTRICIONISTA

-- 1.

sustanciaX :: Heroe -> Heroe
sustanciaX heroe = heroe {resistencia = 0}

cerveza :: [Heroe] -> Heroe -> Heroe
cerveza heroes heroe = heroe {amistades = amistades heroe ++ noAmigos heroes}
    where noAmigos = filter (`notElem` amistades heroe) . map nombreHeroe

-- 2.

saborizador :: String -> Heroe -> Heroe
saborizador gusto heroe = heroe {resistencia = resistencia heroe - length gusto}

ferne' heroe
    | (elem "Chef de Asados" . habilidades) heroe = heroe
    | otherwise = heroe {habilidades = habilidades heroe ++ ["Chef de Asados"]}

-- 3.

gatorei heroe = heroe {resistencia = resistencia heroe + 5 * cantAmigos heroe}
    where cantAmigos = length.amistades

vodka heroe = heroe {nombreHeroe = quitarUltimo.nombreHeroe $ heroe}    
    where quitarUltimo = reverse.drop 1.reverse

vodka' heroe
    | null.nombreHeroe $ heroe = heroe
    | otherwise = heroe {nombreHeroe = init.nombreHeroe $ heroe}

-- 4.

carameloLiquido :: Heroe -> Heroe
carameloLiquido heroe = heroe {resistencia = resistencia heroe - 10}

cocucha :: Heroe -> Heroe
cocucha heroe = heroe {habilidades = quitarPrimero.habilidades $ heroe}
    where quitarPrimero = drop 1

-- MI VILLANO FAVORITO

intentaAtacar :: Amenaza -> Ciudad -> Ciudad
intentaAtacar amenaza ciudad 
    | puedeAtacar amenaza ciudad = efectoCiudad amenaza . fugaPoblacion amenaza $ ciudad
    | otherwise = fugaPoblacion amenaza ciudad 

fugaPoblacion :: Amenaza -> Ciudad -> Ciudad
fugaPoblacion amenaza ciudad  = 
    ciudad {habitantes = max 0 (habitantes ciudad - ((`div` 10).danioPotencial) amenaza)}

efectoMojoJojo :: Ciudad -> Ciudad
efectoMojoJojo = fugaPoblacion mojoJojo

efectoGangrena :: Ciudad -> Ciudad
efectoGangrena ciudad  = 
    ciudad {nombreCiudad = "Gangrena City", habitantes = 2 * habitantes ciudad}

efectoPrincesa :: Ciudad -> Ciudad
efectoPrincesa ciudad = ciudad

aplicarNVeces :: (t -> t) -> Number -> t -> t
aplicarNVeces _ 0 x = x
aplicarNVeces f n x = aplicarNVeces f (n - 1) (f x)

atacaCiudad :: Number -> Amenaza -> Ciudad  -> Number
atacaCiudad n amenaza = habitantes.aplicarNVeces (intentaAtacar amenaza) n

-- ¿VEMOS UNO MAS?

data Capitulo = Capitulo {
    villano :: Amenaza,
    ciudadCapitulo :: String,
    heroeX :: Heroe,
    alimentos :: [Alimento]
} deriving (Show,Eq)

type Alimento = Heroe -> Heroe

darlePlay :: Ciudad -> Capitulo -> Ciudad
darlePlay ciudad capitulo 
    | ciudadCapitulo capitulo /= nombreCiudad ciudad = ciudad
    | otherwise = enfrentamiento capitulo ciudad

enfrentamiento :: Capitulo -> Ciudad -> Ciudad
enfrentamiento (Capitulo villano ciudadCapitulo heroeX alimentos) ciudad
    | (`puedeVencer` villano).(`consumirAlimentos` alimentos) $ heroeX  = ciudad
    | otherwise = intentaAtacar villano ciudad

consumirAlimentos :: Heroe -> [Alimento] -> Heroe
consumirAlimentos = foldr ($)

type Temporada = [Capitulo]

maraton :: Ciudad -> Temporada -> Ciudad
maraton = foldl darlePlay

-- PARA EL TEST

saltadilla = Ciudad {
    nombreCiudad = "Saltadilla",
    habitantes = 21
}

armadillo = Ciudad {
    nombreCiudad = "Armadillo",
    habitantes = 40
}

capitulo1 = Capitulo {
    villano = mojoJojo,
    ciudadCapitulo = "Saltadilla",
    heroeX = burbuja,
    alimentos = [vodka,ferne']
}

capitulo2 = Capitulo {
    villano = bandaGangrena,
    ciudadCapitulo = "Armadillo",
    heroeX = bombon,
    alimentos = [sustanciaX,saborizador "Arandano"]
}

capitulo3 = Capitulo {
    villano = princesa,
    ciudadCapitulo = "Saltadilla",
    heroeX = bellota,
    alimentos = [sustanciaX,gatorei]
}

capitulo4 = Capitulo {
    villano = mojoJojo,
    ciudadCapitulo = "Armadillo",
    heroeX = senioritaBelo,
    alimentos = [cocucha,carameloLiquido]
}

temporada1 = [capitulo1,capitulo2,capitulo3,capitulo4]
// contenidos

class Titulo {
	const property generos
	const actores
	const property esEstreno = true
	
	method valoracion()
	method incluyeGenero(unGenero) = generos.contains(unGenero)
	method incluyeActor(unActor) = actores.contains(unActor)
}

class Pelicula inherits Titulo{
	const duracion // no se usa
	
	//method generos() = generos
	override method valoracion() = 12 * generos.size()
}

class Serie inherits Titulo{
	const temporadas = []
	
	override method valoracion() = self.cantCapitulos()
	
	method cantCapitulos() = temporadas.sum{temp => temp.cantCapitulos()}
	
	method agregarCapitulo(unCapitulo) {
		temporadas.last().agregarCapitulo(unCapitulo)
	}
}

class Temporada {
    const numero // no se usa
    const capitulos = []
    const cantCapMaxima
    
    method cantCapitulos() = capitulos.size()
    
    method agregarCapitulo(unCapitulo) {
    	if (self.cantCapitulos() == cantCapMaxima)
    		throw new TemporadaException(message = "La temporada ya ha finalizado")
    	else 
    		capitulos.add(unCapitulo)
    }
}

class TemporadaException inherits Exception {}

class Capitulo {
    const nombre // no se usa
    const duracion // no se usa
}

class SerieVieja inherits Titulo {
	const temporadas
	const capPorTemp
	override method valoracion() = temporadas * capPorTemp
}

const avengersEndgame = new Pelicula(
	duracion = 182,
	generos = ["accion","drama","aventuras"],
	actores = 
		["Robert Downey Jr.", "Chris Evans", "Mark Ruffalo", "Chris Hemsworth", "Scarlett Johansson", "Jeremy", 
			"Don Cheadle", "Paul Rudd", "Benedict Cumberbatch", "Chadwick Boseman", "Brie Larson", 
				"Tom Holland", "Karen Gillan", "Zoe Saldana"]
)

const blackSails = new Serie(
    generos = ["accion", "drama", "aventuras"],
    actores = ["Toby Stephens", "Luke Arnold", "Toby Schmitz", "Hannah New", "Jessica Parker Kennedy"]
)

const seanEternos = new Serie(
    generos = ["documental"],
    actores = ["Lionel Messi", "Angel Di Maria", "Xavi Hernández", "Luis Suarez"] 
)

const it = new Pelicula(
    duracion = 135,
    generos = ["terror"],
    actores = ["Jaeden Martell", "Jeremy Ray Taylor", "Sophia Lillis", "Finn Wolfhard",
              "Chosen Jacobs"]
)

const elEternoResplandorDeUnaMenteSinRecuerdos= new Pelicula(
    duracion = 108,
    generos = ["drama", "romance", "ficcion"],
    actores = ["Jim Carrey", "Kate Winslet", "Gerry Robert", "Elijah Wood"]

)

const elementos = new Pelicula(
    duracion = 101,
    generos = ["animacion", "comedia", "fantasia"],
    actores = ["Leah Lewis", "Mamoydou Athie", "Ronnie Del Carmen", "Shila Ommi"]
)

const millennium2LaChicaQueSoniabaConUnaCerillaYUnBidonDeGasolina = new Pelicula(
    duracion = 129,
    generos = ["accion", "crimen", "drama", "misterio", "suspenso"],
    actores = ["Michael Nyqvist", "Noomi Rapace", "Lena Endre"]
)

const theWitcher = new Serie(
    generos = ["accion", "fantasia", "drama", "misterio"],
    actores = ["Henry Cavill", "Freya Allan", "Anya Chalotra"]
)

const goodOmens = new Serie(
    generos = ["fantasía", "comedia", "drama"],
    actores = ["David Tennant", "Michael Sheen"]
)
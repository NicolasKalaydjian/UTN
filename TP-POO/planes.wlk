import contenidos.*

// planes

object planBasico {
	const contenidoDisponible = [blackSails, theWitcher, 
		avengersEndgame, elementos, elEternoResplandorDeUnaMenteSinRecuerdos]
		
	method tieneTitulo(unContenido) = contenidoDisponible.contains(unContenido)
	
	method agregarContenido(unContenido) {
		contenidoDisponible.add(unContenido)
	}
}

object planPremium {
	method tieneTitulo(unTitulo) = true
}
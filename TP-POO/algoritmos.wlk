// algoritmos

object valoracionSimilar {
	var property desvio = 0.15
	
	method esVariado() = false
	
	method veriaContenido(unContenido, unPerfil) = 
		if (unPerfil.vioAlgo()) {
			const valoracion = unPerfil.valoracionUsuario()
			unContenido.valoracion().between(valoracion*(1-desvio), valoracion*(1+desvio))
		}
		else
			true
}

class PreferenciaGenero {
	const generos
	
	method esVariado() = generos.size() > 5
	
	method veriaContenido(unContenido, unPerfil) = 
		generos.any{genero => unContenido.incluyeGenero(genero)}
}

class ModoFan {
	const actores
	
	method esVariado() = true
	
	method veriaContenido(unContenido, unPerfil) =
		actores.any{actor => unContenido.incluyeActor(actor)}
}

object porDefecto {
	
	
	// interpretamos que con el algoritmos 
	// por defecto un perfil no es variado
	
	method esVariado() = false
	
	method sonSimilares(contenido1, contenido2) = 
		// inventamos nosotros que significa que 2 contenidos sean "similares"
		// significa que tengan al menos 1 genero en comun
		contenido1.generos().any{genero => contenido2.incluyeGenero(genero)}

	method veriaContenido(unContenido, unPerfil) {
		const lista = unPerfil.contenidosBienPuntuados()
		if (lista == [])
			return unContenido.esEstreno()
		else
			return lista.any({contenido => self.sonSimilares(contenido, unContenido)})
	} 
}


object algoritmoInfantil {
	
	method esVariado() = false
	
	method veriaContenido(unContenido, unPerfil) {
		unContenido.incluyeGenero("infantil")
	}
}




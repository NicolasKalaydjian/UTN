import algoritmos.*
import planes.*
import contenidos.*

// instanciar una cuenta es crear un perfil de usuario

class Cuenta {
	var plan
	
	const property perfiles = []
	
	method crearPerfil(unNombre, unaFecha) {
		const nuevoPerfil = new Perfil(
			nombre = unNombre,
			plan = plan,
			fechaNacimiento = unaFecha
		)
		if(!nuevoPerfil.esMayorDe13())
			nuevoPerfil.cambiarRecomendador(algoritmoInfantil)
		perfiles.add(nuevoPerfil)
	}
		
	// cuando se crean perfiles, a su vez debe crearse el algoritmo, excepto que sea valoracionSimilar
		
	method buscarPerfil(unNombre) = 
		perfiles.find{perfil => perfil.nombre() == unNombre}
	
	method contenidoIdeal(unContenido) = 
		perfiles.all{perfil => perfil.seRecomendaria(unContenido)}
		
	method puedeVer(unTitulo) =
		plan.tieneContenido(unTitulo)
	
	method cambiarPlan(unPlan) {
		plan = unPlan
		perfiles.forEach{perfil => perfil.cambiarPlan(unPlan)}
	}
}

class Perfil {
	const property nombre
	var plan // la cuenta a la que esta asociada el perfil

	const porcentajes = new Dictionary()
	const puntuaciones = new Dictionary()
	
	const property fechaNacimiento // date
	
	var algoritmo = porDefecto
	
	// puede verlo segun el plan? el plan es de la cuenta -> le pregunta a la cuenta
	method puedeVer(unTitulo) = plan.tieneTitulo(unTitulo)
			
	method verContenido(unContenido, unPorcentaje){
		if (!self.puedeVer(unContenido))
			throw new PlanException(message = "el plan no permite ver el contenido")
		else {
			var porcentajeAux = porcentajes.getOrElse(unContenido,{0})
			porcentajeAux += unPorcentaje
			porcentajes.put(unContenido, porcentajeAux)
		}
	}
	
	method contenidosVistos() = porcentajes.keys()
	
	method cantContenidosVistos() = porcentajes.size()
	
	method valoracionUsuario() =
		self.contenidosVistos().sum{contenido => contenido.valoracion()} / 1.max(self.cantContenidosVistos())

	method vioOEstaViendo(unContenido) =
		self.contenidosVistos().contains(unContenido) // TODO
	
	method esVariado() = algoritmo.esVariado()
	
	method veriaContenido(unContenido) = algoritmo.veriaContenido(unContenido, self)

	method seRecomendaria(unContenido) =
		self.veriaContenido(unContenido) and
		(!self.vioOEstaViendo(unContenido))
	
	// si todavia no empezo a ver, devuelve 0%
	method porcentajeVisto(unContenido) =
		porcentajes.getOrElse(unContenido,{0})
		
	method puntuarContenido(unContenido, unaPuntuacion) {
		if (!self.vioOEstaViendo(unContenido))
			throw new PuntuacionException(message = "contenido no visto no se puede puntuar")	
		else 
			if (unaPuntuacion < 1 or unaPuntuacion > 5)
				throw new PuntuacionException(message = "puntuacion no valida")	
			else 
				puntuaciones.put(unContenido, unaPuntuacion)
	}
	
	method contenidosBienPuntuados() = puntuaciones.keys().filter{contenido => puntuaciones.get(contenido) > 3}
	
	method cambiarRecomendador(unAlgoritmo) {
		if(self.esMayorDe13())
			algoritmo = unAlgoritmo
		else 
			algoritmo = algoritmoInfantil
	}
	
	method vioAlgo() = !porcentajes.isEmpty()
	
	method puntuacionDe(unContenido) = puntuaciones.get(unContenido)
	
	method cambiarPlan(unPlan) {
		plan = unPlan
	}
	
	method esMayorDe13() =
		new Date().year() - self.fechaNacimiento().year() >= 13
}

class PlanException inherits Exception {}

class PuntuacionException inherits Exception {}

object repositorio {
	
	const contenidos = []
	
	//method agregarContenido()
	
	method contenidoQueSeRecomendaria(unPerfil) = 
		contenidos.filter{contenido => unPerfil.seRecomendaria(contenido)}
	
	method tieneContenido(unContenido) = contenidos.contains(unContenido)
}
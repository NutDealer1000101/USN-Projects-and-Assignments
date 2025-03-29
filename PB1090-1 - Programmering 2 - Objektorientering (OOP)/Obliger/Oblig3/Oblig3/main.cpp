/*
*   Oblig 3 - Lukas Andersen 272914
*/

/*
						----- Krav (fra oppgaveteksten) -----
X Alle dyr har et navn, tilhører en art, har en vekt, og kan bevege seg.
X Dyrehagen har mulighet til å ta imot nye dyr samt at dyr enten dør eller blir fraktet vekk.
X En klasse som representerer dyrehagen og som holder oversikten over alle dyrene,
		X og som har en funksjon som kan kalles og som løper gjennom alle dyrene og
			presenterer dem (skriver dem ut). Her skal du overlaste operatoren << for
			dyrene.
		X Dette er altså en klasse som holder rede på objekter av de forskjellige andre
			klassene i denne oppgaven.
		X Pekere til disse objektene skal lagres i én vector.
		X Dyrehagen skal ha mulighet til å skrive ut alle dyrene i en gruppe, for
			eksempel pattedyr eller fisk.
X Et hierarki av klasser som representerer dyr.
		X Lag en klasse hver for pattedyr, fugl og fisk.
		X Du skal ikke kunne lage objekter av klassen Dyr. Kun av subklassene.
X Hvert dyr skal ha en medlemsfunksjon bevegelse(), som skriver ut hvordan dyret
	beveger seg (går, hopper, svømmer, fly, el.l)
*/

import std;

namespace la {
	// Alle dyr arver fra denne klassen
	class Dyr {
	public:
		Dyr(std::string_view navn, float vekt)
			:
			navn(navn),
			vekt(vekt) {
		}
		virtual std::string Bevegelse() const = 0;
		std::string Navn() const {
			return navn;
		}
		virtual std::string Art() const = 0;
		float Vekt() const {
			return vekt;
		}
	private:
		std::string navn;
		float vekt;	// enhet: kg
	};

	// Overlaster << operatoren for å kunne printe ut dyr med std::cout
	std::ostream& operator<<(std::ostream& ost, const Dyr& d) {
		return ost << d.Navn() << ": " << d.Art() << ", " << d.Vekt() << "kg, " << d.Bevegelse();
	}

	// Er fortsatt abstrakte siden Art() ikke er laget enda
	class Pattedyr : public Dyr {
	public:
		Pattedyr(std::string_view navn, float vekt)
			:
			Dyr(navn, vekt) {
		}

		std::string Bevegelse() const override {
			return "Gaar";
		}
	};
	class Fugl : public Dyr {
	public:
		Fugl(std::string_view navn, float vekt)
			:
			Dyr(navn, vekt) {
		}

		std::string Bevegelse() const override {
			return "Flyr";
		}
	};
	class Fisk : public Dyr {
	public:
		Fisk(std::string_view navn, float vekt)
			:
			Dyr(navn, vekt) {
		}

		std::string Bevegelse() const override {
			return "Svoemmer";
		}
	};



	// Disse klassene kan vi lage objekter med
	class Bjoorn : public Pattedyr {
	public:
		Bjoorn(std::string_view navn, float vekt)
			:
			Pattedyr(navn, vekt) {
		}
		std::string Art() const override {
			return "Bjoorn";
		}
	};
	class Sebra : public Pattedyr {
	public:
		Sebra(std::string_view navn, float vekt)
			:
			Pattedyr(navn, vekt) {
		}
		std::string Art() const override {
			return "Sebra";
		}
	};
	class Gullfisk : public Fisk {
	public:
		Gullfisk(std::string_view navn, float vekt)
			:
			Fisk(navn, vekt) {
		}
		std::string Art() const override {
			return "Gullfisk";
		}
	};
	class Kampfisk : public Fisk {
	public:
		Kampfisk(std::string_view navn, float vekt)
			:
			Fisk(navn, vekt) {
		}
		std::string Art() const override {
			return "Kampfisk";
		}
	};
	class Lappspurv : public Fugl {
	public:
		Lappspurv(std::string_view navn, float vekt)
			:
			Fugl(navn, vekt) {
		}
		std::string Art() const override {
			return "Lappspurv";
		}
	};
	class Sanglerke : public Fugl {
	public:
		Sanglerke(std::string_view navn, float vekt)
			:
			Fugl(navn, vekt) {
		}
		std::string Art() const override {
			return "Sanglerke";
		}
	};



	class Dyrehage {
	public:
		// Legger til ett dyr av en spessifisert type
		template<typename T>
		void LeggTil(std::string_view navn, float vekt) {
			dyr.push_back(std::make_unique<T>(navn, vekt));
		}

		// Fjerner det første dyret med dette navnet
		void Fjern(std::string_view navn) {
			for (size_t i = 0; i < dyr.size(); i++) {
				if (dyr.at(i)->Navn() == navn) {
					dyr.erase(dyr.begin() + i);
					return;
				}
			}
		}

		// Printer alle dyr
		void PrintAlle() const {
			for (const std::unique_ptr<Dyr>& d : dyr) {
				std::cout << *d << std::endl;
			}
		}

		// Printer alle dyr av en spessifisert art
		template<typename T>
		void PrintArt() const {
			for (const std::unique_ptr<Dyr>& d : dyr) {
				// Henter rå-pekeren (for casting)
				Dyr* raw = d.get();

				// Sjekker om det er mulig å caste pekeren til typen som skal printes ut.
				// Hvis resultatet ikke er nullptr (altså det var mulig), skal den skrives ut.
				if (dynamic_cast<T*>(raw) != nullptr) {
					std::cout << *d << std::endl;
				}
			}
		}
	private:
		// Vectoren som inneholder pekerne til dyra
		std::vector<std::unique_ptr<Dyr>> dyr;
	};
}

int main(int, char**) {
	la::Dyrehage dh;

	dh.LeggTil<la::Bjoorn>("Ole", 100.0f);
	dh.LeggTil<la::Sebra>("Henry", 50.0f);
	dh.LeggTil<la::Gullfisk>("Ida", 0.1f);
	dh.LeggTil<la::Kampfisk>("Erich", 0.05f);
	dh.LeggTil<la::Lappspurv>("Christen", 0.012f);
	dh.LeggTil<la::Sanglerke>("Astrid", 0.007f);

	dh.Fjern("Ida");

	std::println("Printer ut alle dyr:");
	dh.PrintAlle();

	std::println("\nPrinter ut alle pattedyr:");
	dh.PrintArt<la::Pattedyr>();

	std::println("\nPrinter ut alle fisker:");
	dh.PrintArt<la::Fisk>();

	std::println("\nPrinter ut alle fugler:");
	dh.PrintArt<la::Fugl>();
}
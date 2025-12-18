#include "GestionMedicale.h"
#include <iostream>

int main() {
    std::cout << "=== SYSTEME DE GESTION MEDICALE ===" << std::endl;
    std::cout << std::endl;
    
    // ============ TESTS DE LA CLASSE DATE ============
    std::cout << "1. TESTS DE LA CLASSE DATE:" << std::endl;
    
    Date aujourdhui(15, 3, 2024);
    Date demain = aujourdhui + 1;
    Date autreDate(15, 3, 2024);
    
    std::cout << "Date d'aujourd'hui: ";
    aujourdhui.afficher();
    std::cout << std::endl;
    
    std::cout << "Date de demain: ";
    demain.afficher();
    std::cout << std::endl;
    
    if (aujourdhui == autreDate) {
        std::cout << "Les deux dates sont identiques" << std::endl;
    }
    
    if (aujourdhui != demain) {
        std::cout << "Aujourd'hui et demain sont des dates differentes" << std::endl;
    }
    std::cout << std::endl;
    
    // ============ TESTS DE LA CLASSE MEDECIN ============
    std::cout << "2. TESTS DE LA CLASSE MEDECIN:" << std::endl;
    
    Medecin drMartin("Martin", "Cardiologie", 15);
    Medecin drDupont("Dupont", "Pediatrie", 8);
    Medecin drMartin2("Martin", "Cardiologie", 15);
    
    std::cout << "Medecin 1: ";
    drMartin.afficher();
    std::cout << std::endl;
    
    std::cout << "Medecin 2: ";
    drDupont.afficher();
    std::cout << std::endl;
    
    if (drMartin == drMartin2) {
        std::cout << "Les deux cardiologues sont identiques" << std::endl;
    }
    std::cout << std::endl;
    
    // ============ TESTS DE LA CLASSE PATIENT ============
    std::cout << "3. TESTS DE LA CLASSE PATIENT:" << std::endl;
    
    Patient patient1("Jean Dupont", 45, 'M', "PAT12345");
    Patient patient2("Marie Curie", 32, 'F', "PAT67890");
    
    std::cout << "Patient 1: ";
    patient1.afficher();
    std::cout << std::endl;
    
    std::cout << "Patient 2: ";
    patient2.afficher();
    std::cout << std::endl;
    std::cout << std::endl;
    
    // ============ TESTS DE LA CLASSE CONSULTATION ============
    std::cout << "4. TESTS DE LA CLASSE CONSULTATION:" << std::endl;
    
    // Création des consultations
    Consultation consultation1(&drMartin, &patient1, Date(10, 3, 2024), 
                               "Hypertension arterielle");
    Consultation consultation2(&drDupont, &patient2, Date(12, 3, 2024), 
                               "Examen pediatrique de routine");
    
    std::cout << "Consultation 1:" << std::endl;
    consultation1.afficher();
    
    std::cout << "\nConsultation 2:" << std::endl;
    consultation2.afficher();
    
    // ============ DEMONSTRATION DE COMPARAISON ============
    std::cout << "\n5. DEMONSTRATION DE COMPARAISON:" << std::endl;
    
    // Test de comparaison de consultations
    Consultation consultation3(&drMartin, &patient1, Date(10, 3, 2024), 
                               "Controle tension");
    
    if (consultation1 == consultation3) {
        std::cout << "Les consultations 1 et 3 sont identiques (meme medecin, patient et date)" << std::endl;
    } else {
        std::cout << "Les consultations 1 et 3 sont differentes" << std::endl;
    }
    
    if (!(consultation1 == consultation2)) {
        std::cout << "Les consultations 1 et 2 sont differentes" << std::endl;
    }
    
    // ============ EXEMPLE D'UTILISATION PRATIQUE ============
    std::cout << "\n6. EXEMPLE D'UTILISATION PRATIQUE:" << std::endl;
    
    // Ajouter 7 jours à la date d'une consultation
    std::cout << "Prochain rendez-vous pour ";
    patient1.afficher();
    std::cout << " avec ";
    drMartin.afficher();
    std::cout << std::endl;
    
    std::cout << "Date initiale: ";
    consultation1.getDate().afficher();
    std::cout << std::endl;
    
    Date dateSuivante = consultation1.getDate() + 7;
    std::cout << "Prochain controle dans 7 jours: ";
    dateSuivante.afficher();
    std::cout << std::endl;
    
    std::cout << "\n=== FIN DU PROGRAMME ===" << std::endl;
    
    return 0;
}

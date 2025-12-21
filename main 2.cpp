#include "projet_medical.h"
#include <iostream>
#include <vector>

using namespace std;

void testerClassesBasiques() {
    cout << "=== TEST DES CLASSES BASIQUES ===" << endl;
    
    // Test de la classe Date
    Date aujourdhui(15, 12, 2024);
    Date demain = aujourdhui + 1;
    Date hier(14, 12, 2024);
    
    cout << "Aujourd'hui: " << aujourdhui << endl;
    cout << "Demain: " << demain << endl;
    cout << "Hier: " << hier << endl;
    cout << "Aujourd'hui == Hier? " << (aujourdhui == hier ? "Oui" : "Non") << endl;
    cout << "Aujourd'hui + 10 jours: " << (aujourdhui + 10) << endl;
    
    // Test de la classe Medecin
    Medecin medecin1("Dr. Martin", "Cardiologie", 15);
    Medecin medecin2("Dr. Dubois", "Pédiatrie", 10);
    
    cout << "\nMedecin 1: " << medecin1 << endl;
    cout << "Medecin 2: " << medecin2 << endl;
    cout << "Mêmes médecins? " << (medecin1 == medecin2 ? "Oui" : "Non") << endl;
    
    // Test de la classe Patient
    Patient patient1("Jean Dupont", 45, 'M');
    Patient patient2("Marie Curie", 55, 'F');
    
    cout << "\nPatient 1: " << patient1 << endl;
    cout << "Patient 2: " << patient2 << endl;
    cout << "Numéro dossier patient 1: " << patient1.getNumeroDossier() << endl;
    
    // Test de la classe Consultation
    Consultation consultation(medecin1, patient1, aujourdhui, "Examen cardiaque");
    cout << "\nConsultation: " << consultation << endl;
}

void testerFonctionnalites(GestionConsultations& gestion) {
    cout << "\n\n=== TEST DES FONCTIONNALITES SPECIFIQUES ===" << endl;
    
    // 5. Afficher médecins avec consultations à une date donnée
    Date dateTest(15, 12, 2024);
    cout << "\n5. Médecins avec consultations le " << dateTest << ":" << endl;
    auto medecinsDate = gestion.getMedecinsAvecConsultationsALaDate(dateTest);
    for (const auto& medecin : medecinsDate) {
        cout << "  - " << medecin << endl;
    }
    
    // 6. Réserver une consultation
    cout << "\n6. Réservation d'une consultation:" << endl;
    Patient nouveauPatient("Nouveau Patient", 40, 'M');
    gestion.ajouterPatient(nouveauPatient);
    
    Medecin cardiologue = gestion.getMedecins()[0];
    Date dateReservation(20, 12, 2024);
    
    bool reserve = gestion.reserverConsultation(nouveauPatient, cardiologue, dateReservation, "Première consultation");
    if (reserve) {
        cout << "  Réservation réussie!" << endl;
    }
    
    // 7. Consultations d'un patient pendant une période
    cout << "\n7. Consultations d'un patient sur une période:" << endl;
    Patient patientTest = gestion.getPatients()[0];
    Date debut(1, 12, 2024);
    Date fin(31, 12, 2024);
    
    auto consultationsPeriode = gestion.getConsultationsPatientPeriode(patientTest, debut, fin);
    cout << "  Patient: " << patientTest.getNom() << endl;
    cout << "  Période: " << debut << " à " << fin << endl;
    cout << "  Nombre de consultations: " << consultationsPeriode.size() << endl;
    
    // 8. Consultations d'un médecin pendant un mois
    cout << "\n8. Consultations d'un médecin en décembre 2024:" << endl;
    Medecin medecinTest = gestion.getMedecins()[0];
    auto consultationsMois = gestion.getConsultationsMedecinMois(medecinTest, 12, 2024);
    cout << "  Médecin: " << medecinTest.getNom() << endl;
    cout << "  Consultations en décembre: " << consultationsMois.size() << endl;
    
    // 9. Patients avec consultation à une date
    cout << "\n9. Patients avec consultation le " << dateTest << ":" << endl;
    auto patientsDate = gestion.getPatientsAvecConsultationALaDate(dateTest);
    for (const auto& patient : patientsDate) {
        cout << "  - " << patient << endl;
    }
    
    // 10. Patients > 50 ans ayant consulté un cardiologue
    cout << "\n10. Patients > 50 ans ayant consulté un cardiologue:" << endl;
    auto patientsCardio = gestion.getPatientsAge50PlusCardio();
    for (const auto& patient : patientsCardio) {
        cout << "  - " << patient << endl;
    }
    
    // 11. Modifier informations d'un patient
    cout << "\n11. Modification d'un patient:" << endl;
    int dossierAModifier = gestion.getPatients()[0].getNumeroDossier();
    bool modifie = gestion.modifierPatient(dossierAModifier, "Nom Modifié", 50, 'M');
    if (modifie) {
        cout << "  Patient modifié avec succès" << endl;
    }
    
    // 12. Vérifier si un patient est déjà inscrit
    cout << "\n12. Vérification d'inscription:" << endl;
    bool inscrit = gestion.estPatientInscrit(patientTest, medecinTest, dateTest);
    cout << "  Patient " << patientTest.getNom() 
         << " inscrit avec " << medecinTest.getNom() 
         << " le " << dateTest << "? " 
         << (inscrit ? "Oui" : "Non") << endl;
    
    // 13. Nombre de consultations par médecin
    cout << "\n13. Nombre de consultations par médecin:" << endl;
    auto stats = gestion.getNombreConsultationsParMedecin();
    for (const auto& stat : stats) {
        cout << "  " << stat.first.getNom() << ": " << stat.second << " consultation(s)" << endl;
    }
    
    // 14. Consultation la plus complexe
    cout << "\n14. Consultation la plus complexe:" << endl;
    try {
        Consultation plusComplexe = gestion.getConsultationPlusComplexe();
        cout << "  " << plusComplexe << endl;
    } catch (const exception& e) {
        cout << "  " << e.what() << endl;
    }
}

void afficherMenu() {
    cout << "\n=== MENU PRINCIPAL ===" << endl;
    cout << "1. Afficher tous les médecins" << endl;
    cout << "2. Afficher tous les patients" << endl;
    cout << "3. Afficher toutes les consultations" << endl;
    cout << "4. Ajouter un médecin" << endl;
    cout << "5. Ajouter un patient" << endl;
    cout << "6. Réserver une consultation" << endl;
    cout << "7. Rechercher médecins par spécialisation" << endl;
    cout << "8. Vérifier disponibilité d'un médecin" << endl;
    cout << "9. Afficher les statistiques" << endl;
    cout << "10. Tester toutes les fonctionnalités" << endl;
    cout << "0. Quitter" << endl;
    cout << "Votre choix: ";
}

int main() {
    GestionConsultations gestion;
    
    // Ajout de données de test
    gestion.ajouterConsultation(Consultation(
        gestion.getMedecins()[0], 
        gestion.getPatients()[0], 
        Date(15, 12, 2024), 
        "Examen cardiaque régulier"
    ));
    
    gestion.ajouterConsultation(Consultation(
        gestion.getMedecins()[1], 
        gestion.getPatients()[1], 
        Date(16, 12, 2024), 
        "Consultation pédiatrique"
    ));
    
    gestion.ajouterConsultation(Consultation(
        gestion.getMedecins()[0], 
        gestion.getPatients()[2], 
        Date(15, 12, 2024), 
        "Problème cardiaque - traitement prescrit"
    ));
    
    int choix;
    do {
        afficherMenu();
        cin >> choix;
        cin.ignore(); // Pour ignorer le retour chariot
        
        switch (choix) {
            case 1:
                gestion.afficherTousMedecins();
                break;
                
            case 2:
                gestion.afficherTousPatients();
                break;
                
            case 3:
                gestion.afficherToutesConsultations();
                break;
                
            case 4: {
                string nom, specialisation;
                int experience;
                
                cout << "Nom du médecin: ";
                getline(cin, nom);
                cout << "Spécialisation: ";
                getline(cin, specialisation);
                cout << "Années d'expérience: ";
                cin >> experience;
                
                gestion.ajouterMedecin(Medecin(nom, specialisation, experience));
                cout << "Médecin ajouté avec succès!" << endl;
                break;
            }
                
            case 5: {
                string nom;
                int age;
                char sexe;
                
                cout << "Nom du patient: ";
                getline(cin, nom);
                cout << "Âge: ";
                cin >> age;
                cout << "Sexe (M/F): ";
                cin >> sexe;
                
                try {
                    Patient nouveauPatient(nom, age, sexe);
                    gestion.ajouterPatient(nouveauPatient);
                    cout << "Patient ajouté avec succès! Numéro dossier: " 
                         << nouveauPatient.getNumeroDossier() << endl;
                } catch (const exception& e) {
                    cout << "Erreur: " << e.what() << endl;
                }
                break;
            }
                
            case 6: {
                gestion.afficherTousPatients();
                gestion.afficherTousMedecins();
                
                int idxPatient, idxMedecin, jour, mois, annee;
                string diagnostic;
                
                cout << "Index du patient: ";
                cin >> idxPatient;
                cout << "Index du médecin: ";
                cin >> idxMedecin;
                cout << "Date (jour mois annee): ";
                cin >> jour >> mois >> annee;
                cin.ignore();
                cout << "Diagnostic (optionnel): ";
                getline(cin, diagnostic);
                
                if (idxPatient > 0 && idxPatient <= gestion.getPatients().size() &&
                    idxMedecin > 0 && idxMedecin <= gestion.getMedecins().size()) {
                    
                    Date dateResa(jour, mois, annee);
                    bool success = gestion.reserverConsultation(
                        gestion.getPatients()[idxPatient-1],
                        gestion.getMedecins()[idxMedecin-1],
                        dateResa,
                        diagnostic
                    );
                    
                    if (!success) {
                        cout << "Échec de la réservation." << endl;
                    }
                } else {
                    cout << "Index invalide." << endl;
                }
                break;
            }
                
            case 7: {
                string specialisation;
                cout << "Spécialisation à rechercher: ";
                getline(cin, specialisation);
                
                auto medecins = gestion.rechercherMedecinsParSpecialisation(specialisation);
                cout << "Médecins en " << specialisation << ":" << endl;
                for (const auto& medecin : medecins) {
                    cout << "  - " << medecin << endl;
                }
                break;
            }
                
            case 8: {
                int idxMedecin, jour, mois, annee;
                gestion.afficherTousMedecins();
                
                cout << "Index du médecin: ";
                cin >> idxMedecin;
                cout << "Date à vérifier (jour mois annee): ";
                cin >> jour >> mois >> annee;
                
                if (idxMedecin > 0 && idxMedecin <= gestion.getMedecins().size()) {
                    Date dateVerif(jour, mois, annee);
                    bool disponible = gestion.estMedecinDisponible(
                        gestion.getMedecins()[idxMedecin-1],
                        dateVerif
                    );
                    
                    cout << "Le Dr. " << gestion.getMedecins()[idxMedecin-1].getNom()
                         << " est " << (disponible ? "disponible" : "non disponible")
                         << " le " << dateVerif << endl;
                }
                break;
            }
                
            case 9:
                gestion.afficherStatistiques();
                break;
                
            case 10:
                testerClassesBasiques();
                testerFonctionnalites(gestion);
                break;
                
            case 0:
                cout << "Au revoir!" << endl;
                break;
                
            default:
                cout << "Choix invalide!" << endl;
        }
        
        if (choix != 0) {
            cout << "\nAppuyez sur Entrée pour continuer...";
            cin.get();
        }
        
    } while (choix != 0);
    
    return 0;
}
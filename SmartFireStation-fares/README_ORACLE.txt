SMART FIRE STATION — Qt + Oracle (modules Véhicules + Personnel intégrés)
=========================================================================

Application Qt Widgets (C++17) qui réunit le module Véhicules et le module
Personnel dans une seule fenêtre : menu latéral commun + pages Dashboard,
Personnel et Véhicules.

1. Préparer la base Oracle
   - Ouvrir database.sql dans Oracle SQL Developer, connecté avec le schéma
     utilisateur qui possédera les tables, puis exécuter le script (F5).
   - Le schéma crée PERSONNEL, VEHICULE, MISSION, MISSION_PERSONNEL,
     MISSION_VEHICULE, les séquences, les triggers et des lignes d'exemple.
   - Si une table PERSONNEL existe déjà, mise_a_jour_personnel.sql met à jour
     sa structure (colonnes d'authentification) sans la recréer.

2. Ouvrir le projet Qt
   - Ouvrir SmartFireStation.pro dans Qt Creator (ou utiliser CMakeLists.txt).
   - Choisir un kit Qt dont le plugin SQL QODBC correspond à l'architecture
     installée (64 bits). Lancer qmake / Configurer, puis compiler et exécuter.

3. Premier lancement
   - L'application demande l'hôte, le port, le SID/service, l'utilisateur et le
     mot de passe Oracle (valeurs par défaut : localhost, 1521, XE).
   - Connexion via QODBC (pilote Windows « Oracle in XE », 64 bits), connexion
     nommée « SmartFireStationOracle ». Le mot de passe n'est pas enregistré.
   - Une fois Oracle connecté, l'écran de connexion du module Personnel
     s'affiche (authentification, mot de passe haché en SHA-256).
   - Si le pilote QODBC est absent, ou si la connexion est annulée/échoue,
     l'application s'ouvre en mode démonstration : véhicules avec données de
     démonstration, personnel vide. Les modifications en mode démonstration
     ne sont pas enregistrées dans Oracle.

4. Prérequis QODBC
   - Module Qt SQL et plugin QODBC installés pour le kit Qt exact.
   - Pilote ODBC Oracle (« Oracle in XE ») et Oracle Instant Client installés,
     avec une architecture (32/64 bits) correspondant au kit Qt/compilateur.
   - En cas d'échec, lire le message d'erreur et vérifier le nom de service et
     que le listener Oracle est démarré.

Notes sur le Dashboard
----------------------
- Le personnel est lu depuis la table PERSONNEL du schéma ci-dessus.
- La surcharge est conservée : seuil réglable (%) sur le Dashboard, alertes et
  fenêtre de détails. Le nombre de missions provient de MISSION_PERSONNEL joint
  à MISSION (état « EN COURS ») ; charge = min(100, missions × 20 %).
- Le Dashboard est recalculé à chaque affichage pour refléter les modifications
  faites dans la page Personnel.
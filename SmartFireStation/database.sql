-- =====================================================================
--  SMART FIRE STATION MANAGEMENT  -  Modele physique (Oracle 11g XE)
--  Team 2A  -  Projet C++ 2A26  -  2025/2026
--  Executer avec F5 (Run Script) dans SQL Developer,
--  connecte avec VOTRE utilisateur (pas system).
-- =====================================================================

-- ---------------------------------------------------------------------
-- (Optionnel) Nettoyage : a utiliser seulement pour tout recreer
-- ---------------------------------------------------------------------
-- DROP TABLE mission_vehicule CASCADE CONSTRAINTS;
-- DROP TABLE mission_personnel CASCADE CONSTRAINTS;
-- DROP TABLE mission CASCADE CONSTRAINTS;
-- DROP TABLE vehicule CASCADE CONSTRAINTS;
-- DROP TABLE personnel CASCADE CONSTRAINTS;
-- DROP SEQUENCE seq_personnel;
-- DROP SEQUENCE seq_vehicule;
-- DROP SEQUENCE seq_mission;

-- ---------------------------------------------------------------------
-- 1. Sequences (Oracle 11g n'a pas d'auto-increment : on utilise
--    une sequence + un trigger pour generer les ID)
-- ---------------------------------------------------------------------
CREATE SEQUENCE seq_personnel   START WITH 1 INCREMENT BY 1 NOCACHE;
CREATE SEQUENCE seq_vehicule    START WITH 1 INCREMENT BY 1 NOCACHE;
CREATE SEQUENCE seq_mission     START WITH 1 INCREMENT BY 1 NOCACHE;

-- ---------------------------------------------------------------------
-- 2. Tables
-- ---------------------------------------------------------------------

-- Module 1 : Gestion du personnel
-- mot_de_passe et reponse_secrete contiennent des empreintes SHA-256 (jamais le texte en clair).
CREATE TABLE personnel (
    id_personnel     NUMBER         PRIMARY KEY,
    nom              VARCHAR2(50)   NOT NULL,
    prenom           VARCHAR2(50)   NOT NULL,
    grade            VARCHAR2(30),
    poste            VARCHAR2(50),
    telephone        VARCHAR2(15),
    email            VARCHAR2(100)  NOT NULL,
    mot_de_passe     VARCHAR2(255)  NOT NULL,
    question_secrete VARCHAR2(200)  NOT NULL,
    reponse_secrete  VARCHAR2(255)  NOT NULL,
    disponibilite    VARCHAR2(20)   DEFAULT 'Disponible' NOT NULL,
    -- Contraintes d'integrite (memes regles que le controle de saisie en C++)
    CONSTRAINT ck_personnel_tel
        CHECK (telephone IS NULL OR REGEXP_LIKE(REPLACE(REPLACE(telephone, ' ', ''), '-', ''), '^[0-9]{8}$')),
    CONSTRAINT ck_personnel_email
        CHECK (email LIKE '%@%' AND email LIKE '%.%'),
    CONSTRAINT ck_personnel_dispo
        CHECK (disponibilite IN ('Disponible', 'En mission') OR disponibilite LIKE 'En cong%')
);

-- L'email sert d'identifiant de connexion : unique, sans tenir compte des majuscules
CREATE UNIQUE INDEX uq_personnel_email ON personnel (LOWER(email));

-- Module 2 : Gestion des vehicules
CREATE TABLE vehicule (
    id_vehicule      NUMBER         PRIMARY KEY,
    immatriculation  VARCHAR2(20)   NOT NULL UNIQUE,
    type_vehicule    VARCHAR2(30)   NOT NULL,
    modele           VARCHAR2(50),
    etat             VARCHAR2(20)   DEFAULT 'Operationnel' NOT NULL,
    disponibilite    VARCHAR2(20)   DEFAULT 'Disponible' NOT NULL,
    date_maintenance DATE
);

-- Module 3 : Gestion des missions
CREATE TABLE mission (
    id_mission        NUMBER         PRIMARY KEY,
    intitule          VARCHAR2(100)  NOT NULL,
    type_intervention VARCHAR2(50)   NOT NULL,
    lieu              VARCHAR2(100),
    date_mission      DATE,
    priorite          VARCHAR2(20)   DEFAULT 'Moyenne' NOT NULL,
    etat              VARCHAR2(20)   DEFAULT 'Planifiee' NOT NULL,
    description       VARCHAR2(500)
);

-- Table d'association : "ressources affectees" (personnel) - N,N
CREATE TABLE mission_personnel (
    id_mission   NUMBER NOT NULL,
    id_personnel NUMBER NOT NULL,
    CONSTRAINT pk_mission_personnel PRIMARY KEY (id_mission, id_personnel),
    CONSTRAINT fk_mp_mission   FOREIGN KEY (id_mission)
        REFERENCES mission(id_mission)     ON DELETE CASCADE,
    CONSTRAINT fk_mp_personnel FOREIGN KEY (id_personnel)
        REFERENCES personnel(id_personnel) ON DELETE CASCADE
);

-- Table d'association : "ressources affectees" (vehicules) - N,N
CREATE TABLE mission_vehicule (
    id_mission  NUMBER NOT NULL,
    id_vehicule NUMBER NOT NULL,
    CONSTRAINT pk_mission_vehicule PRIMARY KEY (id_mission, id_vehicule),
    CONSTRAINT fk_mv_mission  FOREIGN KEY (id_mission)
        REFERENCES mission(id_mission)   ON DELETE CASCADE,
    CONSTRAINT fk_mv_vehicule FOREIGN KEY (id_vehicule)
        REFERENCES vehicule(id_vehicule) ON DELETE CASCADE
);

-- ---------------------------------------------------------------------
-- 3. Triggers : remplissent l'ID automatiquement si on ne le donne pas
--    (ainsi, dans Qt : INSERT INTO personnel(nom, prenom, ...) VALUES(...))
-- ---------------------------------------------------------------------
CREATE OR REPLACE TRIGGER trg_personnel_bi
BEFORE INSERT ON personnel
FOR EACH ROW
WHEN (NEW.id_personnel IS NULL)
BEGIN
    SELECT seq_personnel.NEXTVAL INTO :NEW.id_personnel FROM dual;
END;
/

CREATE OR REPLACE TRIGGER trg_vehicule_bi
BEFORE INSERT ON vehicule
FOR EACH ROW
WHEN (NEW.id_vehicule IS NULL)
BEGIN
    SELECT seq_vehicule.NEXTVAL INTO :NEW.id_vehicule FROM dual;
END;
/

CREATE OR REPLACE TRIGGER trg_mission_bi
BEFORE INSERT ON mission
FOR EACH ROW
WHEN (NEW.id_mission IS NULL)
BEGIN
    SELECT seq_mission.NEXTVAL INTO :NEW.id_mission FROM dual;
END;
/

-- ---------------------------------------------------------------------
-- 4. Donnees de test (pour verifier que tout fonctionne)
--    Comptes de test : mot de passe = Admin123 ; reponse secrete = tunis
-- ---------------------------------------------------------------------
INSERT INTO personnel (nom, prenom, grade, poste, telephone, email, mot_de_passe, question_secrete, reponse_secrete, disponibilite)
VALUES ('Ben Ali', 'Ahmed', 'Sergent', 'Intervention', '20123456', 'ahmed@station.tn',
        '3b612c75a7b5048a435fb6ec81e52ff92d6d795a8b5a9c17070f6a63c97a53b2', 'Quelle est votre ville de naissance ?', '8a61db0590ce9ed7ae779dc39aaff2aece6bb0eb490e159ff44f4c7aa8e50b0c', 'Disponible');
INSERT INTO personnel (nom, prenom, grade, poste, telephone, email, mot_de_passe, question_secrete, reponse_secrete, disponibilite)
VALUES ('Trabelsi', 'Sami', 'Lieutenant', 'Chef de garde', '22123456', 'sami@station.tn',
        '3b612c75a7b5048a435fb6ec81e52ff92d6d795a8b5a9c17070f6a63c97a53b2', 'Quelle est votre ville de naissance ?', '8a61db0590ce9ed7ae779dc39aaff2aece6bb0eb490e159ff44f4c7aa8e50b0c', 'Disponible');

INSERT INTO vehicule (immatriculation, type_vehicule, modele, etat, disponibilite, date_maintenance)
VALUES ('123 TUN 4567', 'Camion-citerne', 'Renault Midlum', 'Operationnel', 'Disponible',
        TO_DATE('2026-12-01', 'YYYY-MM-DD'));
INSERT INTO vehicule (immatriculation, type_vehicule, modele, etat, disponibilite, date_maintenance)
VALUES ('456 TUN 8910', 'Ambulance', 'Mercedes Sprinter', 'Operationnel', 'Disponible',
        TO_DATE('2026-10-20', 'YYYY-MM-DD'));

INSERT INTO mission (intitule, type_intervention, lieu, date_mission, priorite, etat, description)
VALUES ('Incendie entrepot', 'Incendie', 'Ben Arous', TO_DATE('2026-10-14', 'YYYY-MM-DD'),
        'Haute', 'Planifiee', 'Feu signale dans un entrepot industriel');

-- Affectation : mission 1 -> personnel 1 et 2, vehicule 1
INSERT INTO mission_personnel (id_mission, id_personnel) VALUES (1, 1);
INSERT INTO mission_personnel (id_mission, id_personnel) VALUES (1, 2);
INSERT INTO mission_vehicule  (id_mission, id_vehicule)  VALUES (1, 1);

COMMIT;

-- ---------------------------------------------------------------------
-- 5. Verification
-- ---------------------------------------------------------------------
SELECT * FROM personnel;
SELECT * FROM vehicule;
SELECT * FROM mission;

-- Exemple de jointure : qui est affecte a quelle mission ?
SELECT m.intitule, p.nom, p.prenom
FROM   mission m
JOIN   mission_personnel mp ON mp.id_mission   = m.id_mission
JOIN   personnel p          ON p.id_personnel  = mp.id_personnel;

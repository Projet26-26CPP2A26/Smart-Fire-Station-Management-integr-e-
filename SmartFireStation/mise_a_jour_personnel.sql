-- =====================================================================
--  MISE A JOUR de la table PERSONNEL deja creee (ancienne version de database.sql)
--  Ajoute : mot_de_passe, question_secrete, reponse_secrete + contraintes.
--  A executer UNE SEULE FOIS, avec VOTRE utilisateur, puis F5 (Run Script).
--  Si vous repartez de zero avec le nouveau database.sql, ce fichier est INUTILE.
-- =====================================================================

ALTER TABLE personnel ADD (
    mot_de_passe     VARCHAR2(255),
    question_secrete VARCHAR2(200),
    reponse_secrete  VARCHAR2(255)
);

-- Les membres deja presents recoivent un mot de passe provisoire : Admin123
-- et la reponse secrete : tunis (a changer ensuite avec le bouton Modifier)
UPDATE personnel
SET mot_de_passe     = '3b612c75a7b5048a435fb6ec81e52ff92d6d795a8b5a9c17070f6a63c97a53b2',
    question_secrete = 'Quelle est votre ville de naissance ?',
    reponse_secrete  = '8a61db0590ce9ed7ae779dc39aaff2aece6bb0eb490e159ff44f4c7aa8e50b0c';
COMMIT;

ALTER TABLE personnel MODIFY (
    email            NOT NULL,
    mot_de_passe     NOT NULL,
    question_secrete NOT NULL,
    reponse_secrete  NOT NULL
);

CREATE UNIQUE INDEX uq_personnel_email ON personnel (LOWER(email));

ALTER TABLE personnel ADD CONSTRAINT ck_personnel_tel
    CHECK (telephone IS NULL OR REGEXP_LIKE(REPLACE(REPLACE(telephone, ' ', ''), '-', ''), '^[0-9]{8}$'));
ALTER TABLE personnel ADD CONSTRAINT ck_personnel_email
    CHECK (email LIKE '%@%' AND email LIKE '%.%');
ALTER TABLE personnel ADD CONSTRAINT ck_personnel_dispo
    CHECK (disponibilite IN ('Disponible', 'En mission') OR disponibilite LIKE 'En cong%');

-- Verification : doit afficher 11 colonnes
SELECT column_name FROM user_tab_columns WHERE table_name = 'PERSONNEL' ORDER BY column_id;

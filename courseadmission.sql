-- phpMyAdmin SQL Dump
-- version 5.0.4
-- https://www.phpmyadmin.net/
--
-- Host: localhost:3306
-- Generation Time: Jan 19, 2022 at 07:08 AM
-- Server version: 5.7.24
-- PHP Version: 7.2.19

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `courseadmission`
--

-- --------------------------------------------------------

--
-- Table structure for table `admin`
--

CREATE TABLE `admin` (
  `admin_id` int(100) NOT NULL,
  `admin_username` varchar(200) NOT NULL,
  `admin_password` varchar(200) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `admin`
--

INSERT INTO `admin` (`admin_id`, `admin_username`, `admin_password`) VALUES
(1, 'Admin Mil', '@dmin66198');

-- --------------------------------------------------------

--
-- Table structure for table `application`
--

CREATE TABLE `application` (
  `application_id` int(100) NOT NULL,
  `student_id` int(100) NOT NULL,
  `course1` varchar(100) NOT NULL,
  `course2` varchar(100) NOT NULL,
  `course3` varchar(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `application`
--

INSERT INTO `application` (`application_id`, `student_id`, `course1`, `course2`, `course3`) VALUES
(1, 1, 'AV202', 'CBT702', 'CBT701'),
(2, 3, 'CBT702', 'ACC001', 'HS302'),
(3, 8, 'CBT702', 'CS703', 'CS702'),
(5, 9, 'AV203', 'CS701', 'CS703'),
(6, 10, 'HS302', 'AV201', 'AV202'),
(7, 11, 'ACC001', 'ACC002', 'CS701'),
(8, 12, 'CS702', 'CS703', 'ACC002'),
(9, 13, 'AV201', 'ACC001', 'ACC003'),
(10, 14, 'AV201', 'AV202', 'ACC002'),
(11, 15, 'av201', 'ACC003', 'HS302'),
(12, 16, 'AV202', 'CS702', 'HS302'),
(13, 7, 'AV203', 'ACC003', 'HS302'),
(14, 17, 'CBT702', 'HS301', 'AV201'),
(15, 18, 'AV201', 'ACC002', 'ACC003'),
(16, 27, 'HS301', 'AV201', 'ACC002'),
(17, 29, 'av201', 'cbt702', 'acc003'),
(18, 30, 'av201', 'cbt702', 'acc003');

-- --------------------------------------------------------

--
-- Table structure for table `courses`
--

CREATE TABLE `courses` (
  `course_id` int(100) NOT NULL,
  `faculty_id` int(100) NOT NULL,
  `programme_code` varchar(100) NOT NULL,
  `programme_name` varchar(200) NOT NULL,
  `recommendedCGPA` decimal(10,2) NOT NULL,
  `minimumCGPA` decimal(10,2) NOT NULL,
  `minimumWorkExp` int(100) NOT NULL,
  `numOfStudent` int(100) DEFAULT NULL,
  `approvedStudent` int(100) NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `courses`
--

INSERT INTO `courses` (`course_id`, `faculty_id`, `programme_code`, `programme_name`, `recommendedCGPA`, `minimumCGPA`, `minimumWorkExp`, `numOfStudent`, `approvedStudent`) VALUES
(1, 1, 'AV201', 'Bachelor of Aircraft Engineering Technology in Avionics', '3.00', '2.50', 0, 10, 0),
(2, 1, 'AV202', 'Bachelor of Aircraft Engineering Technology in Mechanical', '3.00', '2.50', 0, 3, 0),
(3, 1, 'AV203', 'Bachelor of Aviation Management', '2.80', '2.50', 0, 4, 0),
(4, 2, 'CS701', 'Bachelor of Information Technology in Computer System Security', '2.80', '2.00', 3, 3, 0),
(5, 2, 'CS702', 'Bachelor of Information Technology in Software Engineering', '2.50', '2.00', 1, 4, 1),
(6, 2, 'CS703', 'Bachelor of Information Technology in Internet of Things', '2.50', '2.00', 1, 3, 0),
(7, 3, 'CBT701', 'Bachelor of Chemical Engineering Technology (Food) with Honours', '2.50', '2.00', 2, NULL, 0),
(8, 3, 'CBT702', 'Bachelor of Chemical Engineering Technology (Environment) with Honours', '2.50', '2.00', 2, 7, 2),
(9, 4, 'ACC001', 'Bachelor of Accountancy', '2.50', '2.00', 2, 4, 0),
(10, 4, 'ACC002', 'Bachelor of Human Resources Management', '2.50', '2.00', 3, 6, 0),
(11, 4, 'ACC003', 'Bachelor of Finance', '2.50', '2.00', 2, 7, 0),
(12, 5, 'HS301', 'Bachelor Of Biomedical Science', '3.00', '2.00', 3, 2, 0),
(13, 5, 'HS302', 'Bachelor Of Occupational Safety & Health', '2.50', '2.00', 1, 5, 1);

-- --------------------------------------------------------

--
-- Table structure for table `faculty`
--

CREATE TABLE `faculty` (
  `faculty_id` int(100) NOT NULL,
  `faculty_name` varchar(200) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `faculty`
--

INSERT INTO `faculty` (`faculty_id`, `faculty_name`) VALUES
(1, 'Faculty of Aviation & Aircraft Maintenance Technology'),
(2, 'Faculty of Computer Science & Mathematics'),
(3, 'Faculty of Chemical Engineering and Bioengineering Technology'),
(4, 'Faculty of Business and Accountancy'),
(5, 'Faculty of Health Sciences');

-- --------------------------------------------------------

--
-- Table structure for table `result`
--

CREATE TABLE `result` (
  `result_id` int(100) NOT NULL,
  `student_id` int(100) NOT NULL,
  `semester` int(100) NOT NULL,
  `gpa` decimal(10,2) NOT NULL,
  `cgpa` decimal(10,2) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `result`
--

INSERT INTO `result` (`result_id`, `student_id`, `semester`, `gpa`, `cgpa`) VALUES
(1, 1, 1, '3.43', '3.43'),
(2, 1, 2, '2.87', '3.13'),
(3, 3, 1, '2.55', '2.55'),
(5, 8, 1, '2.54', '2.54'),
(6, 8, 2, '3.57', '3.11'),
(7, 9, 1, '1.45', '1.45'),
(8, 10, 1, '2.67', '2.67'),
(9, 11, 1, '2.67', '2.67'),
(10, 12, 1, '2.33', '2.33'),
(11, 13, 1, '3.48', '3.48'),
(12, 13, 2, '3.78', '3.62'),
(13, 14, 1, '3.33', '3.33'),
(14, 15, 1, '3.00', '3.00'),
(15, 16, 1, '3.67', '3.67'),
(16, 16, 2, '2.44', '2.93'),
(18, 7, 1, '1.00', '1.00'),
(19, 7, 2, '3.33', '1.93'),
(20, 17, 1, '2.67', '2.67'),
(21, 18, 1, '3.67', '3.67'),
(22, 27, 1, '2.00', '2.00'),
(23, 29, 1, '2.38', '2.38'),
(24, 29, 2, '2.33', '2.37'),
(25, 30, 1, '3.64', '3.64'),
(26, 30, 2, '4.00', '3.72');

-- --------------------------------------------------------

--
-- Table structure for table `student`
--

CREATE TABLE `student` (
  `student_id` int(100) NOT NULL,
  `username` varchar(100) NOT NULL,
  `ic_num` varchar(20) NOT NULL,
  `gender` varchar(20) NOT NULL,
  `email` varchar(50) NOT NULL,
  `password` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `student`
--

INSERT INTO `student` (`student_id`, `username`, `ic_num`, `gender`, `email`, `password`) VALUES
(1, 'Syariff1010', '990226146869', 'Male', 'syariff@yahoo.com', 'Abc123'),
(3, 'naz capeeqqah', '000112148721', 'Female', 'nazcapiqah@yahoo.com', 'nazzy8122'),
(6, 'Adam Fitri226', '001231145221', 'Male', 'fitri_111@yahoo.com', 'f1tr1_00'),
(7, 'Ayaka666', '99829211222', 'Female', 'ayaka666@yahoo.com', 'jhk(11dA'),
(8, 'Yae_Miko', '990421146869', 'Female', 'guuji@yahoo.com', '09812aBB'),
(9, 'Arataki Itto', '990424126522', 'Male', 'ittodesu@gmail.com.my', '1tt0'),
(10, 'AtiqahKoala', '990714062334', 'Female', 'koalaqits@gmail.com', '09k04l4'),
(11, 'Harun122', '000728148871', 'Male', 'harun122@gmail.com', 'HhH@run122'),
(12, 'Fuad Hanabi', '998113014220', 'Male', 'hanabi311@yahoo.com.my', 'h3h3YUi311'),
(13, 'AjimMaster', '950211148281', 'Male', 'ajim_mast3r@yahoo.com', 'qwerTy1092'),
(14, 'Syarifah Kamilea', '990226106559', 'Female', 'lea5859@yahoo.com', 'ch33r1sH'),
(15, 'l337Rahmah', '001231148222', 'Male', 'rahmah__@gmail.com', '906782aB'),
(16, 'Kamil26', '990226125541', 'Male', 'kamil615@yahoo.com', 'Kk@m1l'),
(17, 'Yoimiya', '990225556822', 'Female', 'yoimiya@yahoo.com', '098Abc'),
(18, 'Lembu 778', '123', 'Male', 'cow_the_lembu778@yahoo.com', '12345'),
(27, 'Changmiiiiii', '980331146782', 'Male', 'zhongli@gmail.com', 'Abbbc109cV'),
(29, 'Syarifffff', '910226556869', 'Male', 'sya@yahoo.com.my', 'qw3rtY'),
(30, 'Adam Izhar', '990226166869', 'Male', 'adam@yahoo.com', '123');

-- --------------------------------------------------------

--
-- Table structure for table `studentdetails`
--

CREATE TABLE `studentdetails` (
  `detail_id` int(100) NOT NULL,
  `student_id` int(100) NOT NULL,
  `fullname` varchar(100) NOT NULL,
  `home_address` varchar(100) NOT NULL,
  `phone_num` varchar(100) NOT NULL,
  `marital_status` varchar(20) NOT NULL,
  `education_level` varchar(50) NOT NULL,
  `work_experience` int(100) NOT NULL,
  `make_application` int(100) NOT NULL DEFAULT '0',
  `application_result` varchar(100) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `studentdetails`
--

INSERT INTO `studentdetails` (`detail_id`, `student_id`, `fullname`, `home_address`, `phone_num`, `marital_status`, `education_level`, `work_experience`, `make_application`, `application_result`) VALUES
(1, 1, 'Muhammad Syariff Kamil Bin Sypudin', 'No 26 jalan Kesumba 3A/2', '0199829999', 'Married', 'Diploma', 1, 2, 'CBT702'),
(2, 3, 'Naz Syafiqah Binti Naz', 'No 23 Jalan Kesumba', '0128872333', 'Single', 'Diploma', 0, 1, NULL),
(3, 6, 'Adam Ahmad Fitri Bin Uzair Fitri', 'No 23 Jalan Kesumba 3A/12', '0187223333', 'Single', 'Foundation', 0, 0, NULL),
(4, 8, 'Yae Guuji Miko', 'Jalan Mawar 3, 3B/6, 48300, Bukit Sentosa, Selangor', '01623872223', 'Single', 'A-Level', 1, 2, 'CS702'),
(5, 9, 'Arataki Bin Itto', 'Jalan Inazuma, 4A/3, 48300 Rawang, Selangor', '0176652911', 'Married', 'STPM', 2, 2, NULL),
(6, 10, 'Nurul Atiqah Binti Amin Fuad', 'No 19 Jalan Anggerik 3A/2, Puchong, Selangor', '0118227333', 'Single', 'Matriculation', 0, 2, 'HS302'),
(7, 11, 'Harun Ishak Bin Harun Iskandar', 'No 21, Jalan Teratai, Kluang, Johor', '0175458960', 'Single', 'Matriculation', 0, 1, NULL),
(8, 12, 'Fuad Bin Hashim', 'No 9, Jalan Maya, Seri Kembangan, Selangor', '0179099425', 'Single', 'Diploma', 3, 1, NULL),
(9, 13, 'Furqan Hazim Bin Daud', 'No 99, Jalan Pelita, 4A/8, Ipoh, Perak', '0126296050', 'Married', 'Diploma', 5, 1, NULL),
(10, 14, 'Syarifah Kamilea Binti Bakaruddin', 'No 23, Jalan Penang, Kuala Kubu Bharu, Selangor', '0192223763', 'Single', 'Foundation', 0, 1, NULL),
(11, 15, 'Rahmah Musa Bin Rahmah Idris', 'No 23, Jalan Permai, Seri Kembangan, Selangor', '0175553939', 'Single', 'STPM', 1, 1, NULL),
(12, 16, 'Kamil Bin Sypudin', 'No 42, Jalan Kemboja 4a/12, 48300, Rawang Selangor', '0111111111', 'Single', 'STPM', 4, 1, NULL),
(17, 7, 'Ayaka Binti Ayato', 'No 23 Jalan Permata Indah', '0119654342', 'Divorce', 'STPM', 1, 2, NULL),
(18, 17, 'Yoimiya a/p Lawrence', 'No43 Jalan Teluk Emas', '01876344445', 'Single', 'A-Level', 0, 1, NULL),
(19, 18, 'Harith Adam Bin Huzaifah', 'No 23 Jalan Permai 3', '0176263334', 'Single', 'A-Level', 0, 1, NULL),
(20, 27, 'Zhongli Bin Morax', 'No 45 Jalan Permata Indah 4A/6, Rawang , Selangor', '00000000000000', 'Married', 'Matriculation', 1, 2, NULL),
(21, 29, 'Syariff Kamil', 'Jalan Kemboja', '01982763333', 'Single', 'Diploma', 1, 2, NULL),
(22, 30, 'Adam', 'No 45 Jalan Kemboja', '123455555555', 'Single', 'Diploma', 7, 2, 'cbt702');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `admin`
--
ALTER TABLE `admin`
  ADD PRIMARY KEY (`admin_id`);

--
-- Indexes for table `application`
--
ALTER TABLE `application`
  ADD PRIMARY KEY (`application_id`),
  ADD UNIQUE KEY `student_id` (`student_id`);

--
-- Indexes for table `courses`
--
ALTER TABLE `courses`
  ADD PRIMARY KEY (`course_id`),
  ADD KEY `faculty_id` (`faculty_id`);

--
-- Indexes for table `faculty`
--
ALTER TABLE `faculty`
  ADD PRIMARY KEY (`faculty_id`);

--
-- Indexes for table `result`
--
ALTER TABLE `result`
  ADD PRIMARY KEY (`result_id`),
  ADD KEY `student_id` (`student_id`);

--
-- Indexes for table `student`
--
ALTER TABLE `student`
  ADD PRIMARY KEY (`student_id`);

--
-- Indexes for table `studentdetails`
--
ALTER TABLE `studentdetails`
  ADD PRIMARY KEY (`detail_id`),
  ADD UNIQUE KEY `student_id` (`student_id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `admin`
--
ALTER TABLE `admin`
  MODIFY `admin_id` int(100) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `application`
--
ALTER TABLE `application`
  MODIFY `application_id` int(100) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=19;

--
-- AUTO_INCREMENT for table `courses`
--
ALTER TABLE `courses`
  MODIFY `course_id` int(100) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=14;

--
-- AUTO_INCREMENT for table `faculty`
--
ALTER TABLE `faculty`
  MODIFY `faculty_id` int(100) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;

--
-- AUTO_INCREMENT for table `result`
--
ALTER TABLE `result`
  MODIFY `result_id` int(100) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=27;

--
-- AUTO_INCREMENT for table `student`
--
ALTER TABLE `student`
  MODIFY `student_id` int(100) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=31;

--
-- AUTO_INCREMENT for table `studentdetails`
--
ALTER TABLE `studentdetails`
  MODIFY `detail_id` int(100) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=23;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `application`
--
ALTER TABLE `application`
  ADD CONSTRAINT `application_ibfk_1` FOREIGN KEY (`student_id`) REFERENCES `student` (`student_id`);

--
-- Constraints for table `courses`
--
ALTER TABLE `courses`
  ADD CONSTRAINT `courses_ibfk_1` FOREIGN KEY (`faculty_id`) REFERENCES `faculty` (`faculty_id`);

--
-- Constraints for table `result`
--
ALTER TABLE `result`
  ADD CONSTRAINT `result_ibfk_1` FOREIGN KEY (`student_id`) REFERENCES `student` (`student_id`);

--
-- Constraints for table `studentdetails`
--
ALTER TABLE `studentdetails`
  ADD CONSTRAINT `studentdetails_ibfk_1` FOREIGN KEY (`student_id`) REFERENCES `student` (`student_id`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
